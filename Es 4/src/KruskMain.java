
import java.io.*;  
import java.io.BufferedReader;
import java.util.*;
import java.text.DecimalFormat;



public class KruskMain {
          
    public static void main(String[] args) throws Exception  { 
    
        String thisLine = null;
        
        Graph<Object> gr = new Graph<Object>(true);  //create the Graph for Object
        try {
            BufferedReader br = new BufferedReader(new FileReader("italian_dist_graph.csv")); //loading csv file to Graph using BufferReader library
            while ((thisLine = br.readLine()) != null) {
                String boh[] = thisLine.split(",");
                gr.addNode(boh[0]);
                gr.addNode(boh[1]);
                gr.addArc(boh[0], boh[1], Float.parseFloat(boh[2]));
            }
            System.out.println("File is Loaded OK!!");
            br.close();  
        } catch(Exception e) {
            System.out.println("Error!: "+e);           //throw error if meet a exception 
        }
        KruskMethod(gr);
    }

    public static UnionMakeFind<Integer>  KruskMethod(Graph<Object> gr){        //implementing Krusk Method
        List<Integer> nodes = gr.nodes();                                       //take node from graph.node
        //Collections.sort(nodes);                                                //and order with collection
        UnionMakeFind<Integer> set = new UnionMakeFind<Integer>(nodes);         //create unionfindset all dijoint
        int size = gr.nodes().size();                                           
        int n = 0;
        double boh = 0;
        List<Arc> arcs =  gr.arcs();
        Collections.sort(arcs);                                                 //take all arc and sort
        for (int i = 0; i<arcs.size() && n<(size); i++) {                       //cycle to the arc
            Arc a = arcs.get(i);
            int r1 = set.find(a.from);                                              
            int r2 = set.find(a.to);
            if (r1 != r2) {                                                     //if two node are the different call Union method for merge them
                set.union(r1, r2);
                n++;
                boh += a.etichetta;
                System.out.println(a + " " + r1 + " " + r2 );
            }
        }
        DecimalFormat f = new DecimalFormat("00.#######E0");                    //DecimalFormat its used for have decimal position
        System.out.println("Node "+nodes.size());
        System.out.println("Arc "+n);
        System.out.println("Percoso "+f.format(boh)+" KM");
        return set;
    }      
}
      







