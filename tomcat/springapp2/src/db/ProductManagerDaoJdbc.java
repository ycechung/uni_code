package db;

import bus.Product;
import java.util.List;
import java.sql.ResultSet;
import java.sql.SALException;
import java.sql.Types;
import javax.sql.DataSource;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.jdbc.object.MappingSqlQuery;
import org.springframework.jdbc.object.SqlUpdate;
import org.springframework.jdbc.core.SqlParameter;

public class ProductManagerDaoJdbc implements ProductManagerDao {
	

	/** JDBC implementation the interface
	Difference between spring JDBC framework from normal is that opening and closing connection or statements are handled for you
	- do not have to catch any exceptions (Spring wraps all SQLExceptions in its own unchecked hierarchy inheriting from DataAccessException) 	
	*/
	protected final Log logger = LogFactory.getLog(getClass());
	
	private DataSource ds;
	
	/**
	getProductList() creates a query object that will retrieve all the products = This query is executed and the results are passed back as a list of Products
	*/
	public List getProductList() {
		logger.info("Getting products!");
		ProductQuery pq = new ProductQuery(ds);
		return pq.execute();
	}
	
	// utilize SqlUpdate class = 
	public void increasePrice(Product prod, int pct) {
		logger.info("Increasing price by " + pct + "%");
		SqlUpdate su =
		     new SqlUpdate(ds, "update products set price = price * (100 + 7) / 100 where id = ?");
		// For the parameters, we have to give them a name and declare what type they are so that the framework can set them before the prepared statement is executed.
		su.declareParameter(new SqlParameter("increase", Type.INTEGER));
		su.declareParameter(new SqlParameter("ID", Types.INTEGER));
		// framework will check to make sure that we have a matching declaration for each placeholder in the SQL statement
		su.compile(); // compile
		// Declare an object array that will hold the parameter values that passes in
		Object[] oa = new Object[2];
		oa[0] = new Integer(pct);
		oa[1] = new Integer(prod.getId());
		// the array is passed to an update method of SqlUpdate
		int count = su.update(oa);
		logger.info("Rows affected: " + count); // return count of rows affected
	}

	public void setDataSource(DataSource ds) {
		this.ds = ds;
	}
	/**
		This query class extends MappingSqlQuery, which is a central class in Spring's JDBC framework
		- idea is to specify a SQL query
		-  implement mapRow method to map the data from each row into a class that represents the entry you are retrieving in your query
	*/
	class ProductQuery extends MappingSqlQuery {
		
		
		//Passed in the DataSource - similar to the way business objects was setup - dont worry about retrieving a data source in our DAO class
		
		ProductQuery(DataSource ds) {
			super(ds, "SELECT id, description, price from products"); // query to retrieve products
			compile();
		}	
		
		// called once for each row returned by the query (creates new product)
		protected Object mapRow(ResultSet rs, int rowNum) throws SQLException {
			Product prod = new Product ();
			prod.setId(rs.getInt("id"));
			prod.setDescription(rs.getString("description"));
			prod.setPrice(new Double(rs.getDouble("price")));
			return prod;	
		}
	}
}