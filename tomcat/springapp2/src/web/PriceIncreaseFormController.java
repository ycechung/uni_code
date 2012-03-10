package web;
import org.springframework.web.servlet.mvc.SimpleFormController;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.view.RedirectView;
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
import bus.PriceIncrease;

public class PriceIncreaseFormController extends SimpleFormController {
	 /** Logger for this class and subclasses */
	 protected final Log logger = LogFactory.getLog(getClass());
     private ProductManager prodMan;
     
     public ModelAndView onSubmit(Object command)
     	 throws ServletException {
     	 
     	 int increase = ((PriceIncrease) command).getPercentage();
     	 logger.info("Increasing prices by " + increase + "%.");
     	 prodMan.increasePrice(increase);
     	 String now = (new java.util.Date()).toString();
     	 logger.info("returning from PriceIncreaseForm view to " + getSuccessView());
     	 return new ModelAndView(new RedirectView(getSuccessView()));
     }
     protected Object formBackingObject(HttpServletRequest request) throws ServletException {
     	 PriceIncrease priceIncrease = new PriceIncrease();
     	 priceIncrease.setPercentage(20);
     	 return priceIncrease;
     }
     public void setProductManager(ProductManager pm) {
     	 prodMan = pm;
     }
     public ProductManager getProductManager() {
         return prodMan;    
     }

}