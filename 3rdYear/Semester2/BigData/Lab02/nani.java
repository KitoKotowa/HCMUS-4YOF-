import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.*;d

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class TFIDFReducer
    extends Reducer<Text, Text, Text, Text> {

    private Map<String, Integer> docWordCount = new HashMap<>();
    private Map<String, String> docWords = new HashMap<>();
    private int docWordCount1;

    @Override
    public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
        String docName = " ";
        String value = " ";
        for (Text val : values) {
            StringTokenizer st = new StringTokenizer(val.toString(), " ");
            docName = st.nextToken();
            value = st.nextToken();

            if (docName.compareTo(docWordCount.keySet().iterator().next()) != 0) {
                if (docWordCount.size() > 0) {
                    context.write(new Text(docWordCount.keySet().iterator().next()),
                        new Text(docWordCount1 + "," + docWordCount.get(docName)));
                    docWordCount.clear();
                }
                docWordCount.put(docName, Integer.parseInt(value));
                docWordCount1 = Integer.parseInt(value);
            } else {
                docWordCount.put(docName, docWordCount.get(docName) + Integer.parseInt(value));
                docWordCount1 += Integer.parseInt(value);
            }

            if (!docWords.containsKey(docName)) {
                docWords.put(docName, value);
            } else {
                docWords.put(docName, docWords.get(docName) + " " + value);
            }
        }

        context.write(new Text(docWordCount.keySet().iterator().next()),
            new Text(docWordCount1 + "," + docWordCount.get(docName)));
        docWordCount.clear();

        Iterator it = docWords.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<String, String> pair = (Map.Entry<String, String>)it.next();
            StringTokenizer st = new StringTokenizer(pair.getValue().toString(), ",");
            while (st.hasMoreTokens()) {
                String word = st.nextToken();
                context.write(new Text(word + "," + pair.getKey()),
                    new Text(word + "," + pair.getValue()));
            }
            it.remove();
        }
    }
}