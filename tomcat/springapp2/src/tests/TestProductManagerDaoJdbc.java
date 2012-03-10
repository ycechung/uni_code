package tests;

import java.util.List;
import java.util.ArrayList;
import junit.framework.TestCase;
import org.springframework.jdbc.datasource.DriverManagerDataSource;
import db.ProductManagerDaoJdbc;
import bus.Product;

public class TestProductManagerDaoJdbc extends TestCase {

	private ProductManagerDaoJdbc pmdao;
	
	public void setUp() {
		pmdao = new ProductManagerDaoJdbc();
		DriverManagerDataSource ds = new DriverManagerDataSource();
		ds.setDriverClassName("org.hsqldb.jdbcDriver");
		ds.setUrl("jdbc:hsqldb:db/test");
		ds.setUsername("sa");
		ds.setPassword("");
		pmdao.setDataSource(ds);
	}
	
    public void testGetProductList() {
        List l = pmdao.getProductList();
        Product p1 = (Product) l.get(0);
        assertEquals("Lamp", p1.getDescription());
        Product p2 = (Product) l.get(1);
        assertEquals("Table", p2.getDescription());
    }

    public void testIncreasePrice() {
        List l1 = pmdao.getProductList();
        Product p1 = (Product) l1.get(0);
        assertEquals(new Double("5.78"), p1.getPrice());
        pmdao.increasePrice(p1, 10);
        List l2 = pmdao.getProductList();
        Product p2 = (Product) l2.get(0);
        assertEquals(new Double("6.36"), p2.getPrice());
    }

}