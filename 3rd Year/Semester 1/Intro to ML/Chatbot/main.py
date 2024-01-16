import streamlit as st

from bardapi import Bard
from typing import Any, List, Mapping, Optional
from getpass import getpass

import os
from langchain.chains import RetrievalQA, ConversationalRetrievalChain
from langchain.chains.question_answering import load_qa_chain #-> for load QA
from langchain.indexes import VectorstoreIndexCreator #-> for retrieval QA using vectors index creator. it uses fewer codes with less tokens. So I think this is the best way.
from langchain.document_loaders import TextLoader, PyPDFLoader, DataFrameLoader #-> types of data loader
from langchain.text_splitter import CharacterTextSplitter, RecursiveCharacterTextSplitter #-> to splits data to chunks
from langchain.vectorstores import Chroma # to create a db of chunks
from langchain.embeddings import HuggingFaceEmbeddings, SentenceTransformerEmbeddings

os.environ['_BARD_API_KEY'] = "dwjgofllW12z8zTkVaT-GrkUJvxnb0I4C2HRMnhzzYkiX75RbT9sHfiXzxlxqhgJ8zlFhA."

from langchain.llms.base import LLM
from langchain.callbacks.manager import CallbackManagerForLLMRun
from langchain.prompts.chat import ChatPromptTemplate, HumanMessagePromptTemplate, SystemMessagePromptTemplate

from streamlit_feedback import streamlit_feedback

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
    
def load_embeddings(): 
    embeddings = SentenceTransformerEmbeddings(model_name="keepitreal/vietnamese-sbert")
    db = Chroma(persist_directory="./chroma_index_2", embedding_function=embeddings)
    print("Successfully loading embeddings and indexing")
    return db


def ask_with_memory(vector_store, question, chat_history=[], document_description=""):
    llm=BardLLM()
    retriever = vector_store.as_retriever( # now the vs can return documents
    search_type='similarity', search_kwargs={'k': 3})
 
    general_system_template = f"""
    Use the following pieces of context to answer the question at the end. 
    If you don't know the answer, just say that you don't know, don't try to 
    make up an answer.
    Imagine you're talking to a friend and use natural language and phrasing.
    You can only use Vietnamese do not use other languages.
    Suggest using out searching function for more information.
    ----
    CONTEXT: {{context}}
    ----
    """
    general_user_template = """Here is the next question, remember to only answer if you can from the provided context. 
    If the question is not relevant to real estate , just answer that you do not know, do not create your own answer.
    Do not recommend or propose any infomation of the properties. 
    Be sure to respond in a complete sentence, being comprehensive, including all information in the provided context.
    Imagine you're talking to a friend and use natural language and phrasing.
    Only respond in Vietnamese.
     QUESTION:```{question}```"""

    messages = [
                SystemMessagePromptTemplate.from_template(general_system_template),
                HumanMessagePromptTemplate.from_template(general_user_template)
    ]
    qa_prompt = ChatPromptTemplate.from_messages( messages )


    crc = ConversationalRetrievalChain.from_llm(llm, retriever, combine_docs_chain_kwargs={'prompt': qa_prompt})
    result = crc({'question': question, 'chat_history': chat_history})
    return result


# def main(QUESTION_PROMPT):
#     qa.combine_documents_chain.llm_chain.prompt = QUESTION_PROMPT
#     qa.combine_documents_chain.verbose = True
#     qa.return_source_documents = True
#     st.sidebar.title("Chatbot gợi ý phim")
#     st.sidebar.markdown("### Thành viên nhóm\n1) Trần Thanh Ngân - 21127115\n2) Cao Hoài Yến Vy - 21127205\n3) Châu Tấn Kiệt - 21127329\n4) Hồ Bạch Như Quỳnh - 21127412\n5) Ngô Thị Thanh Thảo - 21127433")
#     st.title("🎥 Chat bot")

#     if 'chat_history' not in st.session_state:
#         st.session_state.chat_history = []

#     user_input = st.text_input("Nhập tin nhắn của bạn:", "")

#     if st.button("Gửi", key='button'):
#         if user_input:
#             with st.spinner("Dữ liệu đang tải, vui lòng đợi..."):
#                 response = qa({"query":user_input,})
#                 st.session_state.chat_history.append({"user": user_input, "bot": response['result']})
#     else:
#         if user_input:
#             with st.spinner("Dữ liệu đang tải, vui lòng đợi..."):
#                 response = qa({"query":user_input,})
#                 st.session_state.chat_history.append({"user": user_input, "bot": response['result']})


#     for chat in st.session_state.chat_history:
#         reply(chat["user"])
#         reply(chat["bot"], " ")


def format_chat_history(chat_history):
    formatted_history = ""
    for entry in chat_history:
        question, answer = entry
        # Added an extra '\n' for the blank line
        formatted_history += f"Question: {question}\nAnswer: {answer}\n\n"
    return formatted_history

def clear_history():
    if "history" in st.session_state:
        st.session_state.history = []
        st.session_state.messages = []

def _submit_feedback(user_response, emoji=None):
    st.toast(f"Feedback submitted: {user_response}", icon=emoji)
    return user_response.update({"some metadata": 123})

# if __name__ == "__main__":
#     llm=BardLLM()
#     embeddings = load_embeddings()
#     qa = RetrievalQA.from_chain_type(
#     llm=llm,
#     chain_type="stuff",
#     retrieverdb.dbas_retriever(search_type="similarity", search_kwargs={"k":10}),
#     return_source_documents=True)
#     question_template = """
#     Use the following pieces of context to answer the question at the end.
#     If you don't know the answer, just say that you don't know, don't try to
#     make up an answer.
#     Imagine you're talking to a friend and use natural language and phrasing.
#     You can only use Vietnamese and do not use other languages.

#     {context}
#     Question: {question}
#     Helpful Answer:
#     """
#     QUESTION_PROMPT = PromptTemplate(
#         template=question_template, input_variables=["question", "context"]
#     )
#     main(QUESTION_PROMPT)

def run_chatbot():
    with st.sidebar.title("Sidebar"):
        if st.button("Clear History"):
            clear_history()

    st.sidebar.title("Chatbot gợi ý phim")
    st.sidebar.markdown("### Thành viên nhóm\n1) Trần Thanh Ngân - 21127115\n2) Cao Hoài Yến Vy - 21127205\n3) Châu Tấn Kiệt - 21127329\n4) Hồ Bạch Như Quỳnh - 21127412\n5) Ngô Thị Thanh Thảo - 21127433")
    st.title("🎥 Movie Chatbot")

    # Initialize the chatbot and load embeddings
    if "messages" not in st.session_state:
        with st.spinner("Đang khởi tạo, xin chờ... !!!"):
            st.session_state.vector_store = load_embeddings()
            st.success("Đã xong!!!")
        st.session_state["messages"] = [{"role": "assistant", "content": "Tôi có thể giúp gì được cho bạn?"}]

    messages = st.session_state.messages
    feedback_kwargs = {
        "feedback_type": "thumbs",
        "optional_text_label": "Please provide extra information",
        "on_submit": _submit_feedback,
    }

    for n, msg in enumerate(messages):
        st.chat_message(msg["role"]).write(msg["content"])

        if msg["role"] == "assistant" and n > 1:
            feedback_key = f"feedback_{int(n/2)}"

            if feedback_key not in st.session_state:
                st.session_state[feedback_key] = None

            streamlit_feedback(
                **feedback_kwargs,
                key=feedback_key,
            )

    chat_history_placeholder = st.empty()
    if "history" not in st.session_state:
        st.session_state.history = []

    if prompt := st.chat_input():
        if "vector_store" in st.session_state:
            vector_store = st.session_state["vector_store"]
            
            q = prompt

            st.session_state.messages.append({"role": "user", "content": prompt})
            st.chat_message("user").write(prompt)

            response = ask_with_memory(vector_store, q, st.session_state.history)

            if len(st.session_state.history) >= 20:
                st.session_state.history = st.session_state.history[1:]

            st.session_state.history.append((q, response['answer']))

            chat_history_str = format_chat_history(st.session_state.history)

            msg = {"role": "assistant", "content": response['answer']}
            st.session_state.messages.append(msg)
            st.chat_message("assistant").write(msg["content"])

            # Display the feedback component after the chatbot responds
            feedback_key = f"feedback_{len(st.session_state.messages) - 1}"
            streamlit_feedback(
                **feedback_kwargs,
                key=feedback_key,
            )    

if __name__ == "__main__":
    run_chatbot()