import org.apache.spark.sql.SparkSession 
import org.apache.spark.sql.functions.{explode, split} 

object SparkStreamingConsumeKafka { 
    def main(args: Array[String]): Unit = { 
        val spark:SparkSession = SparkSession.builder() 
            .master("local[*]") 
            .appName("SparkKafkaExample") 
            .getOrCreate()

        spark.sparkContext.setLogLevel("ERROR") 

        val df = spark.readStream 
            .format("kafka") 
            .option("kafka.bootstrap.servers", "localhost:9092") 
            .option("subscribe", "testTopic") 
            //.option("subscribePattern", "topic.*") 
            .option("startingOffsets", "earliest") // Other possible values assign and latest 
            .load() 

        df.printSchema()

        val groupCount = df.select(explode.split(df("value")," ").alias("word")).groupBy("word").count()
        
        groupCount.writeStream
            .format("console")
            .outputMode("")
            .start()
            .awaitTermination()
    }
}