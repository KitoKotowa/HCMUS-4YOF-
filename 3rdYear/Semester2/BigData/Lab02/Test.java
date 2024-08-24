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
import org.apache.hadoop.mapreduce.lib.input.FileSplit;

public class Test {
    public static class TokenizerMapper extends Mapper<Object, Text, Text, IntWritable> {
        private final static IntWritable one = new IntWritable(1);
        private Text wordCategory = new Text();
        private Text word = new Text();

        // @Override
        // protected void map(Object key, Text value, Context context) throws IOException, InterruptedException {
        //     StringTokenizer tokenizer = new StringTokenizer(value.toString(), ",;\\. \t\n\r\f");
        //     while (tokenizer.hasMoreTokens()) {
        //         String word = tokenizer.nextToken();
        //         int length = word.length();
        //         String s = ((length == 1) ? "Tiny" :
        //                     (length >= 2 && length < 5) ? "Small" :
        //                     (length >= 5 && length <= 9) ? "Medium" : "Big");
        //         wordCategory.set(s);


        //         context.write(wordCategory, one);
        //     }
        // }
        @Override
        public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
            
            FileSplit fileSplit = (FileSplit) context.getInputSplit();
            String filename = fileSplit.getPath().getName();  
            
            int pos = filename.lastIndexOf('.');
            if(pos > -1) {
                filename = filename.substring(0, pos);
            }
            else {
                filename = filename;
            }
            
            StringTokenizer itr = new StringTokenizer(value.toString());
            while (itr.hasMoreTokens()) {
                word.set(itr.nextToken() + "\t" + filename);
                context.write(word, one);
            }
        }


    }

    public static class IntSumReducer extends Reducer<Text, IntWritable, Text, IntWritable> {
        private IntWritable result = new IntWritable();
        @Override
        protected void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            int sum = 0;
            for (IntWritable val : values) {
                sum += val.get();
            }
            
            result.set(sum);
            context.write(key, result);
        }
    }


    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "Test");
        job.setJarByClass(Test.class);
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