package bus;
import java.io.Serializable;

public class Product implements Serializable {
	private String description;
	private Double price;
	private int id; // store value of primary key (used when persist any changes to the object back to db)
	
	public void setId() {
		id = 1;
	}
	
	public int getid() {
		return id;
	}
	
	public void setDescription(String s) {
		description = s;
	}
	public String getDescription() {
		return description;
	}
	public void setPrice(Double d) {
		price = d;
	}
	public Double getPrice() {
		return price;
	}
}