from mrjob.job import MRJob
from mrjob.step import MRStep

class MaxWord(MRJob):
    def steps(self):
        return [
            MRStep(mapper=self.mapper_get_word,
                   combiner=self.combiner_count_word,
                   reducer=self.reducer_count_word),
            MRStep(reducer=self.reducer_find_max_word)
        ]
    
    def mapper_get_word(self, _, line):
        for word in line.split(" "):
            word = word.lower()
            yield word, 1

    def combiner_count_word(self, word, counts):
        yield (word, sum(counts))

    def reducer_count_word(self, word, counts):
        yield None, (sum(counts), word)

    def reducer_find_max_word(self, _, word_count_pairs):
        try:
            yield max(word_count_pairs)
        except ValueError:
            pass

if __name__ == '__main__':
    MaxWord().run()

    