package tests;
import java.util.Map;
import java.util.List;
import java.io.IOException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import junit.framework.TestCase;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.FileSystemXmlApplicationContext;
import org.springframework.web.servlet.ModelAndView;
import web.SpringappController;
import bus.ProductManager;
import bus.Product;

public class TestSpringappController extends TestCase {
	private ApplicationContext ac;
	
	public void setUp() throws IOException {
		ac = new FileSystemXmlApplicationContext("src/tests/WEB-INF/springapp-servlet.xml");
	}
	
	public void testHandleRequest() throws ServletException, IOException {
			SpringappController sc = (SpringappController) ac.getBean("springappController");
			ModelAndView mav = sc.handleRequest((HttpServletRequest) null, (HttpServletResponse) null);
			Map m = mav.getModel();
			List pl = (List) ((Map) m.get("model")).get("products");
			Product p1 = (Product) pl.get(0);
			assertEquals("Lamp", p1.getDescription());
			Product p2 = (Product) pl.get(1);
			assertEquals("Table", p2.getDescription());
			Product p3 = (Product) pl.get(2);
			assertEquals("Chair", p3.getDescription());
	}
	
		
}