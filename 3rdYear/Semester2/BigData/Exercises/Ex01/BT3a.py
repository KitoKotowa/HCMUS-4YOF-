from mrjob.job import MRJob
from mrjob.step import MRStep

class WordCount(MRJob):
    def steps(self):
        return [
            MRStep(mapper=self.mapper_word_count,
                reducer=self.reducer_word_count),
            ]
    def mapper_word_count(self, _, line):
        for word in line.split(" "):
            yield word, 1
    
    def reducer_word_count(self, key, values):
        yield key, sum(values)

if __name__ == '__main__':
    WordCount().run()