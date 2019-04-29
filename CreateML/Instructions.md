### Errors
1. no such module "UIKit"
UIKit belongs to Ios app, not Mac app

2. Expressions are not allowed at the top leve 
For swift, class func cannot be used outside class

3. Could not build AppKit
still not worked out, it happens on Mac but runs good on Macbook(new)

### Dataset
[**CatsDogs**](https://www.microsoft.com/en-us/download/details.aspx?id=54765) for image classifier
**spam.json** for text classifier

### Utils
4. build.py is to form <font color = 'green'>Training Data</font> and <font color = 'green'>Testing Data </font> which are required by CreateMLUI

1) feature
It automatically filter files other than .jpg format
2) how to use
put build.py in same location as image category folders
