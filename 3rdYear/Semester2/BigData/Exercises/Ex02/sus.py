from pyspark.sql import SparkSession
spark = SparkSession.builder\
                    .master("local")\
                    .appName('Ex02')\
                    .getOrCreate()
sc=spark.sparkContext

rdd = sc.textFile("hdfs://localhost:9001/Ex01/input")
rdd = rdd.flatMap(lambda word:word.split()) \
        .map(lambda word:(word,1)) \
        .reduceByKey(lambda x,y:(x+y))

rdd = rdd.saveAsTextFile("hdfs://localhost:9001/wordcountoutput")

spark.stop()
