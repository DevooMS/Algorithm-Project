
import java.util.Hashtable;
import java.util.List;
import java.util.ArrayList;
//import Lib 

//in this class i implemented the structure of a graph using the rappresentation of the adjacency list and with this choice 
//it allow me to comply requirements of the exercise 

public class Graph<T> {
	
	Hashtable<T, Integer> map;
	List<T> nodes;           
	List<List<Arc>> arcs;  //adjacency list in ADT
	int nodeNumber;
    boolean diretto;
	
	public Graph(boolean dir) {     //Describe the struct for the graph
		map = new Hashtable<>(); 
		nodes = new ArrayList<>();
		arcs = new ArrayList<>();
		nodeNumber = 0;
        diretto = dir;
	}
	
	public void addNode(T node) {  //implementing the method for add a node
        if (!map.containsKey(node)) { //map its a hashtable for assign id to the object
            map.put(node, nodeNumber);
            nodes.add(node);           //add the node to the node
            arcs.add(new ArrayList<Arc>()); //crea the adiacence list 
           // System.out.println("Aggiunto nodo: " + node.toString() + " con id: " + nodeNumber);
            nodeNumber++;
        }
	}

    public void addArc(T from, T to, float etichetta) { //implementing the method for add a arc
        int idF = map.get(from);                        //take the id from map and assign to IdFrom
        int idT = map.get(to);                           //take the id from map and assign to IdTo
		if (!hasArc(from, to)) {                        //this avoid duplicates and arc to the node
			arcs.get(idF).add(new Arc(idF, idT, etichetta));
			if (diretto) {                                    //check if its directed or not if not add reverse arc
				arcs.get(idT).add(new Arc(idT, idF, etichetta));
			}
        //    System.out.println("Aggiunto arco da: " + from.toString() + " a: " + to.toString());
		}
    }

    public boolean hasNode(T node) {                    //check if have a node if yes return true else false
        if (map.containsKey(node)) {
            return true;
        }
        return false;
    }

    public boolean hasArc(T from, T to) {           //check if have a arc if yes return true else false
        int idF = map.get(from);
        int idT = map.get(to);
        if (arcs.get(idF) != null) {
            if (arcs.get(idF).contains(new Arc(idF, idT, 0))) {
                return true;
            }
        }
        return false;
    }

    public void deleteNode(T node) {                 //this method implementing Remove node
        int idN = map.get(node);
        map.remove(node);
        arcs.remove(node);
        nodes.remove(node);
        for (int i = 0; i<nodeNumber; i++) {        //in this cycle, arcs ispected from the list of arc and removed if connected to the node
            Arc a = new Arc(i, idN, 0);
            arcs.get(i).remove(a);
        }
        nodeNumber--;
    }

    public void deleteArc(T from, T to) {           //remove arcs and if directed remove reverse arcs
        int idF = map.get(from);
        int idT = map.get(to);
        Arc a = new Arc(idF, idT, 0);
        arcs.get(idF).remove(a);
        if (diretto) {
            a = new Arc(idT, idF, 0);
            arcs.get(idT).remove(a);
        }
    }

    public int nodeNumber() {                     //return number of node
        return map.size();
    }

    public int arcNumber() {                     //return number of arc
        int s = 0;
        for (int i = 0; i<nodeNumber; i++) {
            s += arcs.get(i).size();
        }
        return s;
    }

    public List<Integer> nodes() {              //return list of node 
        return new ArrayList<Integer>(map.values());
    }

    public List<Arc> arcs() {                   //return list of arc 
        List<Arc> result = new ArrayList<>();
        for (int i = 0; i<nodeNumber; i++){
            result.addAll(arcs.get(i));
        }
        return result;
    }

    public float etichetta(T from, T to) {      //return the weight 
        int idF = map.get(from);
        int idT = map.get(to);
        Arc a = new Arc(idF, idT, 0);
        if (arcs.get(idF)!=null) {
            return arcs.get(idF).get(arcs.get(idF).indexOf(a)).etichetta;
        }
        return 0;
    }

}
