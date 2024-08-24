import org.apache.spark.sql.SparkSession 
import org.apache.spark.sql.functions._ 
object WordCountDF { 
    def main(args:Array[String]): Unit = { 
        val spark:SparkSession = SparkSession.builder() 
            .master("local[*]") 
            .appName("WordCountDF") 
            .getOrCreate() 
    // Turn off INFO message, display ERROR only 
    spark.sparkContext.setLogLevel("ERROR") 
    import spark.implicits._ 
    // Read text file into DataFrame 
    val df = spark.read.text("file:///usr/local/spark/input/input.txt") 
    // Apply Split and Explode 
    val df_exploded = df.withColumn("word", explode(split($"value", " "))) 
    // Group by word and count 
    val df_count = df_exploded.groupBy("word") 
                    .count() 
                    .orderBy($"count".desc) 
// Display Output 
    df_count.show() 
// Save word count results to text file 
// df_count.write.text("file:///usr/local/spark/output/wordCountDF")     
} 
} 