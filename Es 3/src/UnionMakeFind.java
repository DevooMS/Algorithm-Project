package src;
import java.util.Hashtable;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class UnionMakeFind<T> {     //implenting UNION MAKE FIND
  
    int lastId;
    int nodeNumber;
    Hashtable<T, Integer> map;
    List<Integer> parent;
    List<Integer> size;
    
    public UnionMakeFind(List<T> elements) {       //create a new list for the elements ("MAKE")
      lastId = 0;
      nodeNumber = elements.size();
      map = new Hashtable<>(nodeNumber);
      parent = new ArrayList<>(nodeNumber);
      size = new ArrayList<>(nodeNumber);
      
    //  System.out.println("AAA"+elements);
      for (int i = 0; i<nodeNumber; i++) {
        add(elements.get(i));
      }
     // System.out.println("UnionFind iniziale: " + parent.toString());
    }
    
    public void add(T element) {                //add the element to the set 
      if (!map.containsKey(element)) {
        map.put(element, lastId);
        parent.add(lastId);
        size.add(1);
        lastId++;
      }
    }
    
    public int find(T element) {                //its used to find the root of the elements
      int p = map.get(element);
      //System.out.println("FIND: "+p+" " + element.toString());
      while (p != parent.get(p)) {              //if parent its different from itself contine the algoritm
        //int q = parent.get(p);
        //parent.set(p, parent.get(q));
        p = parent.get(p);                      
      }
      return p;
    }
    
    public void union(T x, T y) {             //this method its used for implementing "UNION"
      int xr = find(x);                       //call find of the first node  and save to the variable xr
      int yr = find(y);                        //call find of the second node  and save to the variable yr
      if (xr != yr) {                          // if xr are different yr 
        if (size.get(xr) < size.get(yr)) {     //if are different check the size of the subset and then set the larger as the root of the shorter
          parent.set(xr, yr);
          size.set(yr, size.get(yr) + size.get(xr));
        }
        else {
          parent.set(yr, xr);
          size.set(xr, size.get(yr) + size.get(xr));
        }
      }
    }
    public String toString(){
      return parent.toString();
    }

    public int maxsize() {                //take the biggest subset
      return Collections.max(size);
    }
  }