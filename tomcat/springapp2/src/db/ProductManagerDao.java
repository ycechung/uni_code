package db;

import bus.Product;
import java.util.List;

public interface ProductManagerDao {
	public List getProductList ();
	
	public void increasePrice(Product prod, int pct);

}