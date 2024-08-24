import java.io.IOException;
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

public class MoneyCount {
    public static class TokenizerMapper extends Mapper<Object, Text, Text, FloatWritable> {
        private final static FloatWritable one = new IntWritable(1);
        private Text wordCategory = new Text();

        @Override
        protected void map(Object key, Text value, Context context) throws IOException, InterruptedException {
            // StringTokenizer tokenizer = new StringTokenizer(value.toString(), ",;\\. \t\n\r\f");
            // while (tokenizer.hasMoreTokens()) {
            //     String word = tokenizer.nextToken();
            //     int length = word.length();
            //     String s = ((length == 1) ? "Tiny" :
            //                 (length >= 2 && length < 5) ? "Small" :
            //                 (length >= 5 && length <= 9) ? "Medium" : "Big");
            //     wordCategory.set(s);
            //     context.write(wordCategory, one);
            // }

            // while (itr.hasMoreTokens()) {
            //     word.set(itr.nextToken() + "\t" + filename);
            //     context.write(word, one);
            // }
            String lines = value.toString();
            String items[] = lines.split("\\t");
            String item = items[1];
            float price = item.length();
            if (item.endsWith("*")) {
                price *= 0.8;
            }
            context.write(context.write(items[0], price));
        
        }
    }

    public static class IntSumReducer extends Reducer<Text, IntWritable, Text, IntWritable> {
        private FloatWritable result = new IntWritable();
        @Override
        protected void reduce(Text key, Iterable<FloatWritable> values, Context context) throws IOException, InterruptedException {
            float sum = 0;
            for (FloatWritable val : values) {
                sum += val.get();
            }
            result.set(sum);
            context.write(key, result);
        }
    }

    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "MoneyCount");
        job.setJarByClass(MoneyCount.class);
        job.setMapperClass(TokenizerMapper.class);
        job.setCombinerClass(IntSumReducer.class);
        job.setReducerClass(IntSumReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}   