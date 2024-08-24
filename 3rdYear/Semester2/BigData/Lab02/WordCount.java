import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class WordCount {

    public static class TokenizerMapper extends Mapper<Object, Text, Text, Text> {

        private Text outputKey = new Text();
        private Text outputValue = new Text();

        public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
            StringTokenizer itr = new StringTokenizer(value.toString());
            while (itr.hasMoreTokens()) {
                String termI = itr.nextToken();
                String documentId = itr.nextToken();
                double frequency = Double.parseDouble(itr.nextToken());

                outputKey.set(term); 
                outputValue.set(documentId + " " + frequency); 
                context.write(outputKey, outputValue);
            }
        }
    }

    public static class FrequencyFilterReducer extends Reducer<Text, Text, Text, Text> {

        private Text outputValue = new Text();

        public void reduce(Text key, Iterable<Text> values, Context context)
                throws IOException, InterruptedException {
            int totalFrequency = 0;
            Map<String, Double> frequencyMap = new HashMap<>();

            for (Text val : values) {
                String[] parts = val.toString().split(" ");
                String documentId = parts[0];
                double frequency = Double.parseDouble(parts[1]);
                frequencyMap.put(documentId, frequency);
                totalFrequency += frequency;
            }

            if (totalFrequency >= 3) {
                for (Map.Entry<String, Double> entry : frequencyMap.entrySet()) {
                    outputValue.set(entry.getKey() + " " + entry.getValue());
                    context.write(key, outputValue);
                }
            }
        }
    }

    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "term frequency filter");
        job.setJarByClass(WordCount.class);
        job.setMapperClass(TokenizerMapper.class);
        job.setCombinerClass(FrequencyFilterReducer.class);
        job.setReducerClass(FrequencyFilterReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}