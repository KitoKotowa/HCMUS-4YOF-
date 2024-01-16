import streamlit as st
import numpy as np
import re
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from bardapi import Bard
from typing import Any, List, Mapping, Optional
from getpass import getpass
import os
from langchain.chains import RetrievalQA #-> for retrieval QA
from langchain.chains.question_answering import load_qa_chain #-> for load QA
from langchain.indexes import VectorstoreIndexCreator #-> for retrieval QA using vectors index creator. it uses fewer codes with less tokens. So I think this is the best way.
from langchain.document_loaders import TextLoader, PyPDFLoader, DataFrameLoader #-> types of data loader
from langchain.text_splitter import CharacterTextSplitter, RecursiveCharacterTextSplitter #-> to splits data to chunks
from langchain.vectorstores import Chroma #to create a db of chunks
from langchain.embeddings import HuggingFaceEmbeddings, SentenceTransformerEmbeddings
from langchain import PromptTemplate
os.environ['_BARD_API_KEY'] = "dwjgofllW12z8zTkVaT-GrkUJvxnb0I4C2HRMnhzzYkiX75RbT9sHfiXzxlxqhgJ8zlFhA."
from langchain.llms.base import LLM
from langchain.callbacks.manager import CallbackManagerForLLMRun

class BardLLM(LLM):
    @property
    def _llm_type(self) -> str:
        return "custom"

    def _call(
        self,
        prompt: str,
        stop: Optional[List[str]] = None,
        run_manager: Optional[CallbackManagerForLLMRun] = None,
    ) -> str:
        response = Bard(token=os.environ['_BARD_API_KEY']).get_answer(prompt)['content']
        return response

    @property
    def _identifying_params(self) -> Mapping[str, Any]:
        """Get the identifying parameters."""
        return {}

def reply(message, role="user"):
    if role == "user":
        st.text("You: " + message)
    else:
        st.text("Bot: " + message)

def clean_title(title):
    return re.sub("[^a-zA-Z0-9 ]", "", title)

def search(title, vectorizer, movies, tfidf):
    title = clean_title(title)
    query_rec = vectorizer.transform([title])
    similarity = cosine_similarity(query_rec,tfidf).flatten()
    indices = np.argpartition(similarity, -5)[-5:]
    results = movies.iloc[indices][::-1]
    return results

def read_data(movies):
    movies["clean_title"] = movies["title"].apply(clean_title)
    vectorizer = TfidfVectorizer(ngram_range=(1,2))
    tfidf = vectorizer.fit_transform(movies["clean_title"])
    title = "Toy Story 1995"
    find_film(title, vectorizer, tfidf, movies)

def find_film(title, vectorizer, tfidf, movies):
    query_rec = vectorizer.transform([title])
    similarity = cosine_similarity(query_rec,tfidf).flatten()
    indices = np.argpartition(similarity, -5)[-5:]
    results = movies.iloc[indices][::-1]
    titles = results['title'].values
    titles_str = ', '.join(titles)
    st.markdown(titles_str)

def main(QUESTION_PROMPT):
    qa.combine_documents_chain.llm_chain.prompt = QUESTION_PROMPT
    qa.combine_documents_chain.verbose = True
    qa.return_source_documents = True
    st.sidebar.title("Chatbot gợi ý phim")
    st.sidebar.markdown("### Thành viên nhóm\n1) Trần Thanh Ngân - 21127115\n2) Cao Hoài Yến Vy - 21127205\n3) Châu Tấn Kiệt - 21127329\n4) Hồ Bạch Như Quỳnh - 21127412\n5) Ngô Thị Thanh Thảo - 21127433")
    st.title("🎥 Chat bot")

    if 'chat_history' not in st.session_state:
        st.session_state.chat_history = []

    user_input = st.chat_input("Nhập thông tin mà bạn cần gợi ý: ")

    if st.button("Gửi", key='button'):
        if user_input:
            with st.spinner("Dữ liệu đang tải, vui lòng đợi..."):
                response = qa({"query":user_input,})
                st.session_state.chat_history.append({"user": user_input, "bot": response['result']})
    else:
        if user_input:
            with st.spinner("Dữ liệu đang tải, vui lòng đợi..."):
                response = qa({"query":user_input,})
                st.session_state.chat_history.append({"user": user_input, "bot": response['result']})


    for chat in st.session_state.chat_history:
        reply(chat["user"])
        reply(chat["bot"], " ")

if __name__ == "__main__":
    llm=BardLLM()
    embeddings = SentenceTransformerEmbeddings(model_name="keepitreal/vietnamese-sbert")
    db = Chroma(persist_directory="./chroma_index_2", embedding_function=embeddings)
    qa = RetrievalQA.from_chain_type(
    llm=llm,
    chain_type="stuff",
    retriever=db.as_retriever(search_type="similarity", search_kwargs={"k":10}),
    return_source_documents=True)
    question_template = """
    Use the following pieces of context to answer the question at the end.
    If you don't know the answer, just say that you don't know, don't try to
    make up an answer.
    Imagine you're talking to a friend and use natural language and phrasing.
    You can only use Vietnamese and do not use other languages.

    {context}
    Question: {question}
    Helpful Answer:
    """
    QUESTION_PROMPT = PromptTemplate(
        template=question_template, input_variables=["question", "context"]
    )
    main(QUESTION_PROMPT)
