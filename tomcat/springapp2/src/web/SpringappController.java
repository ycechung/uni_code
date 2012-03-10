package web;
import org.springframework.web.servlet.mvc.Controller;
import org.springframework.web.servlet.ModelAndView;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;
import java.util.HashMap;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import bus.Product;
import bus.ProductManager;


public class SpringappController implements Controller {    
	/* Logger for this class and subclasses 
	STEP 12: Create a View
	  The model that this class returns is actually resolved via a ViewResolver. 
	  Since we have not specified a specific one, we are going to get a default one that just forwards to a url matching the name of the view specified. 
	*/
	protected final Log logger = LogFactory.getLog(getClass());
	
	private ProductManager prodMan;
	
	public ModelAndView handleRequest(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException{
		
				String now = (new java.util.Date()).toString();
				logger.info("returning hello view with " + now);

		        Map myModel = new HashMap();
		        myModel.put("now", now);
		        myModel.put("products", getProductManager().getProducts());
		
		        
		        return new ModelAndView("hello", "model", myModel);

	}
	

    public void setProductManager(ProductManager pm) {
        prodMan = pm;
    }

    public ProductManager getProductManager() {
        return prodMan;
    }

}