import static org.junit.Assert.*;

import org.junit.Test;

public class unitTest {
boolean istrue = true;

	@Test
	public void testTestIsValid() {
// UrlValidator with default properties
	UrlValidator val = new UrlValidator();
	assertTrue(istrue);									//make sure true actually evaluates to true
	for(int idx = 0; idx < validUrls.length; idx++) {   //known valid urls should pass
		assertTrue(val.isValid(validUrls[idx]));
	}
	for(int idx = 0; idx < invalidUrls.length; idx++) {
		assertFalse(val.isValid(invalidUrls[idx]));		//known invalid urs should fail
	}
	
//	UrlValidator with null (http, https, ftp is valid)
	UrlValidator valNULL = new UrlValidator(null);
	for(int idx = 0; idx < validUrls.length; idx++) {   //known valid urls should pass
		assertTrue(valNULL.isValid(validUrls[idx]));
	}
	for(int idx = 0; idx < invalidUrls.length; idx++) {
		assertFalse(valNULL.isValid(invalidUrls[idx]));		//known invalid urs should fail
	}
// UrlValidator with specific schemes passed
	String[] scheme = {"http"};
	UrlValidator valHTTP = new UrlValidator(scheme);
	for(int idx = 0; idx < validHttp.length; idx++) {	//known http should pass
		assertTrue(valHTTP.isValid(validHttp[idx]));
	}
	for(int idx = 0; idx < validHttps.length; idx++) {	//https will fail
		assertFalse(valHTTP.isValid(validHttps[idx]));
	}	
	for(int idx = 0; idx < validftp.length; idx++) {	//ftp will fail
		assertFalse(valHTTP.isValid(validftp[idx]));
	}
	String[] httpsscheme = {"https"};
	UrlValidator valHTTPS = new UrlValidator(httpsscheme);
	for(int idx = 0; idx < validHttps.length; idx++) {	//known https should pass
		assertTrue(valHTTPS.isValid(validHttps[idx]));
	}
	for(int idx = 0; idx < validHttp.length; idx++) {	//http will fail
		assertFalse(valHTTPS.isValid(validHttp[idx]));
	}	
	for(int idx = 0; idx < validftp.length; idx++) {	//ftp will fail
		assertFalse(valHTTPS.isValid(validftp[idx]));
	}
	String[] ftpscheme = {"ftp"};
	UrlValidator valFTP = new UrlValidator(ftpscheme);
	for(int idx = 0; idx < validftp.length; idx++) {	//known ftp will pass
		assertTrue(valFTP.isValid(validftp[idx]));
	}for(int idx = 0; idx < validHttps.length; idx++) {	// https will fail
		assertFalse(valFTP.isValid(validHttps[idx]));
	}
	for(int idx = 0; idx < validHttp.length; idx++) {	//http will fail
		assertFalse(valFTP.isValid(validHttp[idx]));
	}	
		
//	UrlValidator with specific options (ALLOW_2_SLASHES, NO_FRAGMENTS)
		

	
	}
	
//	collections of urls
	String[] validUrls = {
//			valid schemes
			"http://www.example.com",
			"https://www.example.com",
			"ftp://www.example.com",
//			valid authority
			"http://this.oops.com",
			"http://8.6.com",
			"http://[1001:0db8:0000:0042:0000:8a2e:0370:7334]", //ipv6
			"http://8.6.com:11",
			"http://6.6.6.6", //ipv4
//			valid path
			"http://yeet.co/",
			"http://yeet.co/86",
			"http://yeet.au/this/path",
//			valid query
			"http://yeetube.co?yeet",
			"http://yeetube.co?yeet=ye&yolo=no"	
	};
	String[] validHttp = {
//			valid schemes
			"http://www.example.com",
//			valid authority
			"http://this.oops.com",
			"http://8.6.com",
			"http://[1001:0db8:0000:0042:0000:8a2e:0370:7334]", //ipv6
			"http://8.6.com:11",
			"http://6.6.6.6", //ipv4
//			valid path
			"http://yeet.co/",
			"http://yeet.co/86",
			"http://yeet.au/this/path",
//			valid query
			"http://yeetube.co?yeet",
			"http://yeetube.co?yeet=ye&yolo=no"	
	};
	String[] validHttps = {
//			valid schemes
			"https://www.example.com",
//			valid authority
			"https://this.oops.com",
			"https://8.6.com",
			"https://[1001:0db8:0000:0042:0000:8a2e:0370:7334]", //ipv6
			"https://8.6.com:11",
			"https://6.6.6.6", //ipv4
//			valid path
			"https://yeet.co/",
			"https://yeet.co/86",
			"https://yeet.au/this/path",
//			valid query
			"https://yeetube.co?yeet",
			"https://yeetube.co?yeet=ye&yolo=no"	
			
	};	String[] validftp = {
//			valid schemes
			"ftp://www.example.com",
//			valid authority
			"ftp://this.oops.com",
			"ftp://8.6.com",
			"ftp://[1001:0db8:0000:0042:0000:8a2e:0370:7334]", //ipv6
			"ftp://8.6.com:11",
			"ftp://6.6.6.6", //ipv4
//			valid path
			"ftp://yeet.co/",
			"ftp://yeet.co/86",
			"ftp://yeet.au/this/path",
//			valid query
			"ftp://yeetube.co?yeet",
			"ftp://yeetube.co?yeet=ye&yolo=no"	
	};
	
	
	String[] invalidUrls = {
//			invalid schemes
			"ttp://www.example.com",
			"htps://www.example.com",
			"1tp://www.example.com",
//			invalid authority
			"http://this.oops.com.3",
			"http://8.6.c",
			"http://.1",
			"http://8.6.:11",
			"http://6.6.6.6.6",
			"http://[1001:0db8:0000:0042:0000:8a2e:0370:733411]",
//			invalid path
			"http://yeet.co/..",
			"http://yeet.co//86",
			"http://yeet.au/this//path"
	};

}

