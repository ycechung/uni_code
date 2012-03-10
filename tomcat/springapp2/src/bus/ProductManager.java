package bus;
import java.io.Serializable;
import java.util.ListIterator;
import java.util.List;
import db.ProductManagerDao;

public class ProductManager implements Serializable {
	private	ProductManagerDao pmd;
	private List products;
	
	public void setProductManagerDao(ProductManagerDao pmd) {
		this.pmd = pmd;
	}
	
/*
	public void setProducts(List p) {
		products = p;
	}
*/
	// each time getProducts is called, it will go and query the database
	public List getProducts() {
		products = pmd.getProductList();
		return products;
	}
	
	// increasePrice will delegate to the DAO to increase the price and the new price will be reflected the next time getProducts is called
	public void increasePrice(int pct) {
		ListIterator li = products.listIterator();
		while (li.hasNext ()) {
			Product p = (Product) li.next();
			/*
			double newPrice = p.getPrice().doubleValue() * (100 + pct)/100;
			p.setPrice(new Double(newPrice));
			*/
			pmd.increasePrice(p, pct);
		}	
	}
	
}