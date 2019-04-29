//
//  GameViewController.swift
//  TriMatch
//
//  Created by sj on 2018/7/3.
//  Copyright © 2018 sj. All rights reserved.
//

import UIKit

class GameViewController: UIViewController {

    var sub: UIView!
    var show: UIView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let tap = UITapGestureRecognizer(target: self, action: #selector(self.tapHandle(_:)))
        let pan = UIPanGestureRecognizer(target: self, action: #selector(self.panHandle(_:)))
        let pinch = UIPinchGestureRecognizer(target: self, action: #selector(self.pinchHandle(_:)))
        let longPress = UILongPressGestureRecognizer(target: self, action: #selector(self.longPressHandle(_:)))
        let rotation = UIRotationGestureRecognizer(target: self, action: #selector(self.rotationHandle(_:)))
        
        let screen = UIScreenEdgePanGestureRecognizer(target: self, action: #selector(self.screenHandle(_:)))
        screen.edges = .left //要具体指明，all不行，不然没反应
        screen.delegate = self
        
        let swipeLeft = UISwipeGestureRecognizer(target: self, action: #selector(self.swipeHandle(_:)))
        swipeLeft.direction = .left
        swipeLeft.require(toFail: pan)
        let swipeRight = UISwipeGestureRecognizer(target: self, action: #selector(self.swipeHandle(_:)))
        swipeRight.direction = .right
        swipeRight.require(toFail: pan)
        let swipeUp = UISwipeGestureRecognizer(target: self, action: #selector(self.swipeHandle(_:)))
        swipeUp.direction = .up
        swipeUp.require(toFail: pan)
        let swipeDown = UISwipeGestureRecognizer(target: self, action: #selector(self.swipeHandle(_:)))
        swipeDown.direction = .down
        swipeDown.require(toFail: pan)
  
        self.view.backgroundColor = UIColor.black
        sub = UIView(frame: CGRect(x: 0, y: 0, width: 100, height: 500))
        sub.backgroundColor = UIColor.yellow
        sub.tag = 1
        self.view.addSubview(sub)
        
        
        show = UIView(frame: CGRect(x: 0, y: 0, width: 100, height: 200))
        show.backgroundColor = UIColor.red
        show.tag = 2
        self.view.addSubview(show)
       
        
        //7个手势检测
        self.view.addGestureRecognizer(swipeDown)
        self.view.addGestureRecognizer(swipeUp)
        self.view.addGestureRecognizer(swipeLeft)
        self.view.addGestureRecognizer(swipeRight)
        self.view.addGestureRecognizer(tap)
        //self.view.addGestureRecognizer(pan) //pan打开会导致swipe无法识别，这两个一起用需谨慎
        self.view.addGestureRecognizer(pinch)
        self.view.addGestureRecognizer(longPress)
        self.view.addGestureRecognizer(rotation)
        self.view.addGestureRecognizer(screen)
    }
    

  
    @objc func tapHandle(_ sender: Any) {
        print("tap \n");
    }
    
    @objc func swipeHandle(_ sender: Any){
        let gesture: UISwipeGestureRecognizer = sender as! UISwipeGestureRecognizer
        if gesture.direction == .left {
            print("swipe left \n")
            
        } else if gesture.direction == .right {
            print("swipe right \n")
            
        } else if gesture.direction == .up {
            print("swipe up \n")
            
        } else if gesture.direction == .down {
            print("swipe down \n")
        }
    }

    @objc func panHandle(_ sender: Any) {
        print("pan \n");
    }
    
    @objc func pinchHandle(_ sender: Any) {
        print("pinch \n");
    }
    
    @objc func longPressHandle(_ sender: Any) {
        print("longPress \n");
    }
    
    @objc func rotationHandle(_ sender: Any) {
        print("rotation \n");
    }
    
    @objc func screenHandle(_ sender: UIScreenEdgePanGestureRecognizer) {
        if sender.edges == .left {
            print("screenEdgePan Left \n")
        } else if sender.edges == .right {
            print("screenEdgePan Right \n")
        } else if sender.edges == .top {
            print("screenEdgePan Top \n")
        } else if sender.edges == .bottom {
            print("screenEdgePan Bottom \n")
        }
        
        
        let hitView = self.view.hitTest(sender.location(in: sender.view), with: nil)
        print(hitView?.tag)
    
        /*
        if sender.state == .began {
            print("began \n")
        } else if sender.state == .changed {
            print("changed \n")
        } else if sender.state == .ended {
            print("ended \n")
        } else if sender.state == .cancelled {
            print("cancelled \n")
        } else if sender.state == .failed {
            print("failed \n")
        } else if sender.state == .possible {
            print("possible \n")
        } else if sender.state == .recognized {
            print("recognized \n")
        }*/
        
        
        if sender.state == .began || sender.state == .changed {
            let trans: CGPoint = sender.translation(in: sender.view)
            print(trans)
            
                hitView?.frame.size.width += trans.x / 10
        } else {
            UIView.animate(withDuration: 1) {
                hitView?.frame.size.width = 100
            }
        }
        
        
    }
    
    /*---------End Gesture ---------*/
    


}


extension GKRandomSource {
    func dicByShufflingObjects(in dict: NSMutableDictionary) -> NSMutableDictionary {
        var keys = dict.allKeys
        self.arrayByShufflingObjects(in: keys)
        let final: NSMutableDictionary = [:]
        for i in 0..<keys.count {
            final[keys[i]] = dict.value(forKey: keys[i] as! String)
        }
        return final
    }
}



extension GameViewController: UIGestureRecognizerDelegate {

}
