//manipulate js in UIWebView

import UIKit

class WebViewController: UIViewController, UIWebViewDelegate{

    @IBOutlet var webView: UIWebView!
    override func viewDidLoad() {
        super.viewDidLoad()
     
        self.webView.backgroundColor = UIColor.clear
        self.webView.scalesPageToFit = true
        self.webView.delegate = self
        let url: URL = URL(string: "http://192.168.1.2/assets/test1.png")!
        let url2: URL = URL(string: "https://www.baidu.com")!
        let request: URLRequest = URLRequest(url: url2)
        self.webView.loadRequest(request)
        
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    func webViewDidStartLoad(_ webView: UIWebView) {
        print("start")
    }

    
    var i: Int = 0
    func webViewDidFinishLoad(_ webView: UIWebView) {
        print("finish")
        
        let url = self.webView.stringByEvaluatingJavaScript(from: "document.location.href")
        let title = self.webView.stringByEvaluatingJavaScript(from: "document.title")
        print("current url: ", url!)
        print("current title: ", title!)
        
        
        if i == 0 {
            self.webView.stringByEvaluatingJavaScript(from: "document.getElementsByName('wd')[0].value='www.jobyme88.com';")
            self.webView.stringByEvaluatingJavaScript(from: "document.forms[0].submit();")
            i += 1
        }
        

        
        if i == 3 {
            self.webView.stringByEvaluatingJavaScript(from:
                "var script = document.createElement('script');" +
                    "script.type = 'text/javascript';" +
                    "script.text = \"function myFunction() { " +
                    "var field = document.getElementsByName('wd')[0]; " +
                    "field.value = 'www.boygirl88.com'; " +
                    "document.forms[0].submit(); " +
                    "}\";" +
                "document.getElementsByTagName('head')[0].appendChild(script);"
            )
            self.webView.stringByEvaluatingJavaScript(from: "myFunction()")
            i += 1
        }
    }
    
    
    func webView(_ webView: UIWebView, didFailLoadWithError error: Error) {
        print(error.localizedDescription)
    }
    
    
    func webView(_ webView: UIWebView, shouldStartLoadWith request: URLRequest, navigationType: UIWebViewNavigationType) -> Bool {
        print("should start")
        return true
    }
 


}
