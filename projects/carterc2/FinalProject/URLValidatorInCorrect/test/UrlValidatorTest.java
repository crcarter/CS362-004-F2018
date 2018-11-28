

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	
	   boolean withError = false;  // Change to true to see it crash
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   if (urlVal.isValid("http://www.google.com")) {
	      System.out.println("url is valid");
	   } else {
	      System.out.println("url is invalid");
	   }
	   String str = "http://www.google.com";
	   boolean result = urlVal.isValid(str);
	   System.out.println(result + " " + str);
	   assertTrue(result); 
	   str = "http://www.google.com/";
	   result = urlVal.isValid(str);
	   System.out.println(result + " " + str);
	   assertTrue(result);  
	   str = "http://www.google.com/$23?action=edit&mode=up";
	   result = urlVal.isValid(str);
	   System.out.println(result + " " + str);
	   assertTrue(result);  
	   // Error here
	   if (withError) {
		   str = "ftp://www.google.com/";
		   result = urlVal.isValid(str);
		   System.out.println(result + " " + str);
		   assertTrue(result);
		   str = "ftp://go.au/$23?action=edit&mode=up";
		   result = urlVal.isValid(str);
		   System.out.println(result + " " + str);
		   assertTrue(result);  
		   str = "h3t://255.255.255.255:65535?action=view";
		   result = urlVal.isValid(str);
		   System.out.println(result + " " + str);
		   assertTrue(result);  
		   str = "h3t://255.com/test1/file?action=edit&mode=up";
		   result = urlVal.isValid(str);
		   System.out.println(result + " " + str);
		   assertTrue(result);  
	   }
	   
	   
	   // Invalid
	   str = "http://www.google.com/\\";
	   result = urlVal.isValid(str);
	   System.out.println(result + " " + str);
	   str = "http://www.google.com/..";
	   result = urlVal.isValid(str);
	   System.out.println(result + " " + str);
	   //assertTrue(result);   
	   str = "http:/www.google.com/";
	   result = urlVal.isValid(str);
	   System.out.println(result + " " + str);
	   str = "http:/www.google.com";
	   result = urlVal.isValid(str);
	   System.out.println(result + " " + str);
	   str = "://www.google.com/";
	   result = urlVal.isValid(str);
	   System.out.println(result + " " + str);

	   System.out.println("End manual testing.");
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
   }
   


}
