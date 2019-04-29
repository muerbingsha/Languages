//open front camera and capture photo

import UIKit
import AVFoundation
import Photos

class AlbumViewController: UIViewController, AVCapturePhotoCaptureDelegate {

    let cameraView = UIView(frame: CGRect(origin: .zero, size: CGSize(width: 300, height: 300)))
    
    var session = AVCaptureSession()
    let photoOutput = AVCapturePhotoOutput()
    var pl = AVCaptureVideoPreviewLayer()
    
    
    func getDevice(position: AVCaptureDevice.Position) -> AVCaptureDevice? {
        //method 1 - specific
        let d1 = AVCaptureDevice.default(for: .video)
        let d2 = AVCaptureDevice.default(.builtInDualCamera, for: .video, position: .front)
        
        
        //method 2 - sets of devices
        var deviceTypes = [AVCaptureDevice.DeviceType.builtInDualCamera,
                           .builtInMicrophone,
                           .builtInTelephotoCamera,
                           .builtInWideAngleCamera]
        
        if #available(iOS 11.1, *) {
            deviceTypes.append(AVCaptureDevice.DeviceType.builtInTrueDepthCamera)
        }
        
        let s = AVCaptureDevice.DiscoverySession(
            deviceTypes: deviceTypes,
            mediaType: AVMediaType.video,
            position: AVCaptureDevice.Position.unspecified)
        for device in s.devices {
            if device.position == position {
                return device
            } else {
                return nil
            }
        }
        return nil
    }
    
    override func viewWillAppear(_ animated: Bool) {
        
        //configure session
        session.beginConfiguration()
        
        //choose device
        let videoDevice = AVCaptureDevice.default(.builtInWideAngleCamera, for: AVMediaType.video, position: .front)
        
        //add inputs
        guard
            let videoInput = try? AVCaptureDeviceInput(device: videoDevice!),
            session.canAddInput(videoInput)
            else {
            fatalError("not video input")
        }
        session.addInput(videoInput)
        
        //add outputs
        if session.canAddOutput(photoOutput) {
            session.addOutput(photoOutput)
            session.sessionPreset = .photo
            session.commitConfiguration()
        }
        
        //configure preview
        pl.session = session
        pl.videoGravity = .resizeAspectFill
        pl.connection?.videoOrientation = .portrait
        self.cameraView.layer.addSublayer(pl)
 
    }
    
    
    override func viewWillLayoutSubviews() {
        pl.frame = cameraView.bounds
    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.view.backgroundColor = UIColor.red
        self.view.addSubview(cameraView)
        
        //btn: open camera
        let btn = UIButton(type: .roundedRect)
        btn.frame = CGRect(x: 100, y: 100, width: 100, height: 50)
        self.view.addSubview(btn)
        let img = UIImage(named: "UI.bundle/btn.jpg")
        btn.frame.size = CGSize(width: img!.size.width * 0.5, height: img!.size.height * 0.5)
        btn.setTitle("open camera", for: .normal)
        btn.titleLabel?.font = UIFont.systemFont(ofSize: 20)
        btn.titleLabel?.baselineAdjustment = .alignBaselines
        btn.setBackgroundImage(img, for: .normal)
        btn.addTarget(self, action: #selector(self.openCamera), for: .touchUpInside)
        
        
        //duplicate UIButton
        //UIButton does not conform to NSCopying, UIButton.copy will occur error
        //However, it does conform to NSCoding, so you can archive the current instance, then unarchive a 'copy'.
        let data: Data = NSKeyedArchiver.archivedData(withRootObject: btn)
        let btn2: UIButton = NSKeyedUnarchiver.unarchiveObject(with: data) as! UIButton
        //btn: snap photo
        self.view.addSubview(btn2)
        btn2.addTarget(self, action: #selector(self.snapPhoto), for: .touchUpInside)
        btn2.frame.origin.y = btn.frame.origin.y + btn.frame.height + 200
        btn2.setTitle("snap photo", for: .normal)
        btn2.setBackgroundImage(img, for: .normal) //copy missed
    }


    @objc func openCamera(){
        print("good")
        session.startRunning()
    }
    
    
    @objc func snapPhoto(){
        print("snap photo")
        
        var setting = AVCapturePhotoSettings(format: [AVVideoCodecKey: AVVideoCodecType.jpeg])
        photoOutput.capturePhoto(with: setting, delegate: self) //create kasa sound
    }
    
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    
   
    //MARK: delegates
    func photoOutput(_ output: AVCapturePhotoOutput, willBeginCaptureFor resolvedSettings: AVCaptureResolvedPhotoSettings) {
        print("willBeginCapture")
    }
    
    
    func photoOutput(_ output: AVCapturePhotoOutput, willCapturePhotoFor resolvedSettings: AVCaptureResolvedPhotoSettings) {
        print("willCapturePhotoFor")
    }
    
    
    func photoOutput(_ output: AVCapturePhotoOutput, didCapturePhotoFor resolvedSettings: AVCaptureResolvedPhotoSettings) {
        print("didCapturePhotoFor")
    }
    
    
    func photoOutput(_ output: AVCapturePhotoOutput, didFinishProcessingPhoto photo: AVCapturePhoto, error: Error?) {
        print("didFinishProcessingPhoto")
        
        //check error
        guard error == nil else {
            print(error)
            return
        }
        
        //check authorization
        PHPhotoLibrary.requestAuthorization { (status) in
            guard status == PHAuthorizationStatus.authorized else {
                fatalError("not permitted to use photo")
            }
            
            PHPhotoLibrary.shared().performChanges({
                let createRequest = PHAssetCreationRequest.forAsset()
                createRequest.addResource(with: .photo, data: photo.fileDataRepresentation()!, options: nil)
            }, completionHandler: { (bb, error) in
                print(error)
            })
        }
    }

    
    func photoOutput(_ output: AVCapturePhotoOutput, didFinishCaptureFor resolvedSettings: AVCaptureResolvedPhotoSettings, error: Error?) {
        print("didFinishCapotureFor")
    }
    
    
    func photoOutput(_ output: AVCapturePhotoOutput, didFinishRecordingLivePhotoMovieForEventualFileAt outputFileURL: URL, resolvedSettings: AVCaptureResolvedPhotoSettings) {
        print("didFinishRecordingLive")
   
        
        
    }
    
    
    func photoOutput(_ output: AVCapturePhotoOutput, didFinishProcessingLivePhotoToMovieFileAt outputFileURL: URL, duration: CMTime, photoDisplayTime: CMTime, resolvedSettings: AVCaptureResolvedPhotoSettings, error: Error?) {
        print("didFinishProcessingLive")
    }



}


