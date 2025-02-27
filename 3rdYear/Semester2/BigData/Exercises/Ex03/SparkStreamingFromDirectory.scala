import org.apache.spark.sql.SparkSession 
import org.apache.spark.sql.types.{IntegerType, StringType, StructField, StructType} 
 
object SparkStreamingFromDirectory { 
 
  def main(args: Array[String]): Unit = { 
 
    val spark:SparkSession = SparkSession.builder() 
      .master("local[*]") 
      .appName("DirectorySparkExample") 
      .getOrCreate() 
 
    spark.sparkContext.setLogLevel("ERROR") 
 
    val schema = StructType( 
      List( 
        StructField("RecordNumber", IntegerType, true), 
        StructField("Zipcode", StringType, true), 
        StructField("ZipCodeType", StringType, true), 
        StructField("City", StringType, true), 
        StructField("State", StringType, true), 
        StructField("LocationType", StringType, true), 
        StructField("Lat", StringType, true), 
        StructField("Long", StringType, true), 
        StructField("Xaxis", StringType, true), 
        StructField("Yaxis", StringType, true), 
        StructField("Zaxis", StringType, true), 
        StructField("WorldRegion", StringType, true), 
        StructField("Country", StringType, true), 
        StructField("LocationText", StringType, true), 
        StructField("Location", StringType, true), 
        StructField("Decommisioned", StringType, true) 
      ) 
    ) 
 
    val df = spark.readStream 
      .schema(schema) 
      .json("file:///usr/local/spark/stream_data/zipcodes") 
 
    df.printSchema() 
 
    val groupDF = df.select("Zipcode") 
        .groupBy("Zipcode").count() 
    groupDF.printSchema() 
 
    groupDF.writeStream 
      .format("console") 
      .outputMode("complete") 
      .start() 
      .awaitTermination() 
  }
}