public class Arc implements Comparable<Arc>{      //arc its a library and its used to describe arcs
    public int from;
    public int to;
    public float etichetta;

    public Arc(int f, int t, float e) {         //describe f=from t=to e=etichetta
		from = f;
		to = t;
		etichetta = e;
	}
	
	public int compareTo(Arc to) {              //its used for implement compareTo method.
		return Math.round(etichetta - to.etichetta);
	}

    public boolean equals(Object a) {             //its used for know if an arc have equal start and end
        if (!(a instanceof Arc)) {                //check if instance of arc          
            return false;
        }
        return from == ((Arc) a).from && to == ((Arc) a).to;  //upcasting from object to arc
    }

    public String toString() {                          //toString its used for print .
        return "From " + from + " to " + to + ": " + etichetta;
    }
}
