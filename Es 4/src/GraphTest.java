import java.util.List;
//import java.util.Collections;


import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import org.junit.Before;
import org.junit.Test;

public class GraphTest {              
	
	private Object s1, s2, s3;
	List<Integer> nodes;
	private float peso12 = 1;
	private float peso13 = 2;
	private Graph<Object> graph;
	
	@Before                                                     //Before its used for assign a basic graph before call test
	public void createGraph() throws Exception {
		s1 = "Nodo1";
		s2 = 12345;
		s3 = "Nodo3";
		graph = new Graph<Object>(true);
		graph.addNode(s1);
		graph.addNode(s2);
		graph.addArc(s1, s2, peso12);
	}

	@Test
	public void testNodeNumber() throws Exception {
		assertEquals(graph.nodes().size(), 2);
	}

	@Test
	public void testAddNode() throws Exception {
		graph.addNode(s3);
		assertEquals(graph.nodes().size(), 3);
	}

	@Test
	public void testHasNode() throws Exception {
		assertTrue(graph.hasNode(s1));
		assertFalse(graph.hasNode(s3));
	}

	@Test
	public void testDeleteNode() throws Exception {
		graph.deleteNode(s2);
		assertFalse(graph.hasNode(s2));
		
	}

	@Test
	public void testArcNumber() throws Exception {
		assertEquals(graph.arcNumber(), 2);
	}

	@Test
	public void testAddArc() throws Exception {
		graph.addNode(s3);
		graph.addArc(s1, s3, peso13);
		assertEquals(graph.arcNumber(), 4);
	}
	
	@Test
	public void testHasArc() throws Exception {
		assertTrue(graph.hasArc(s1, s2));
	}
	
	@Test
	public void testDeleteArc() throws Exception {
		graph.deleteArc(s1, s2);
		assertEquals(graph.arcNumber(), 0);
	}
}