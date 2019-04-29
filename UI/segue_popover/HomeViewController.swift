import UIKit

class HomeViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    

    //1
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "toLandVC" {
            let pop = segue.destination
            pop.popoverPresentationController?.delegate = self
        }
    }

}

//2
extension HomeViewController: UIPopoverPresentationControllerDelegate {
    func adaptivePresentationStyle(for controller: UIPresentationController) -> UIModalPresentationStyle {
        return .none
    }
}
