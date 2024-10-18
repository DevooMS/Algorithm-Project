package src;

import java.util.List;
import java.util.ArrayList;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

public class UnionMakeFindTest {			   
	
	private Integer i1, i2, i3;
	private UnionMakeFind<Object> set;
	
	@Before			//create the basic union make find of generic type
	public void createUnionMakeFind() throws Exception {
	
		i1 = 0;
		i2 = 1;
		i3 = 2;
		List<Object> elements = new ArrayList<>();
		elements.add(i1);
		elements.add(i2);
		
		set = new UnionMakeFind<Object>(elements);
	}

	@Test			//check if it has two elements 
	public void testElementNumber() throws Exception {
		assertEquals(set.lastId, 2);
	}
	
	@Test			//add a element and check if the size its three
	public void testAdd() throws Exception {  //~da risolvere
		
		set.add(i3);
		assertEquals(set.lastId, 3);
	}

	@Test			//check if the elements are disjoint
	public void testFind() throws Exception {
	/*	assertTrue(i1.equals(set.find(i1)));
    	assertTrue(i2.equals(set.find(i2)));*/
		
		//System.out.println(i2);
		//System.out.println(set.find(i2));
		assertTrue(i2 == set.find(i2));
	}
	
	
	@Test			//add duplicate and size its same
	public void testAddDuplicate() throws Exception {
		set.add(i1);
		assertEquals(set.lastId, 2);
	}
	

	@Test			//merge the elements and check they have same root
	public void testUnion() throws Exception {
		set.union(i1, i2);
		assertEquals(set.find(i1), set.find(i2));
	}

}