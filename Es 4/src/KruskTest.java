import java.util.List;
import java.util.Collections;


import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

public class KruskTest {              
	
	private Object s1, s2, s3;
	List<Integer> nodes;
	private float peso = 1;
	private UnionMakeFind<Integer> set;
	
	@Before                                                     //Before its used for assign a basic graph before call test
	public void createUnionMakeFind() throws Exception {
		s1 = "Nodo1";
		s2 = 12345;
		s3 = "Nodo3";
		Graph<Object> gr = new Graph<Object>(true);
		gr.addNode(s1);
		gr.addNode(s2);
		gr.addNode(s3);
		gr.addArc(s1, s2, peso);
		set = KruskMain.KruskMethod(gr);
		nodes = gr.nodes();
		Collections.sort(nodes);
	}

	@Test
	public void testElementNumber() throws Exception {									//test if have 3 nodes
		assertEquals(set.lastId, 3);
	}

	@Test
	public void testLargestNode() throws Exception {									//test if after krusk the depth its 2
		assertEquals(set.maxsize(), 2);
	}

	@Test
		public void testRootEquals() throws Exception {									//test the first and the second have same root
		assertEquals(set.find(nodes.get(0)), set.find(nodes.get(1)));
	}

	@Test
		public void testRootDifferent() throws Exception {								//test the first and the third are different
		assertTrue(set.find(nodes.get(0)) != set.find(nodes.get(2)));
	}
}