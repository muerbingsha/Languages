//optimize: turn Int to Any


import Foundation


class HTDemo {
    var data: [Int] = []
    var hashTable: Dictionary<Int, Int> = [:]
    var eleCount: Int {
        return data.count
    }
    var usedHashM: HashMethod
    var usedConflictM: ConflictMethod
    
    enum HashMethod {
        case directLocate // a * key + b
        case getReminder  // key % count
    }
    
    enum ConflictMethod {
        case linearProbe  // (key + 1) % count
        case randomProbe  // (key + ran) % count
    }
    
    
    
    //issue: call non-funtion type
    //solution: check whether function name conflicts with function passed variable
    //issue: use local variable before declaration
    //solution: check missing closure
    init(data: [Int], hash: HashMethod, conflict: ConflictMethod) {
        self.data = data
        self.usedHashM = hash
        self.usedConflictM = conflict
        
        for ele in data {
            let k = getValidKey(ele: ele)
            hashTable[k] = ele
        }
    
    }
    
    func hashFunc(ele: Int, method: HashMethod) -> Int {
        switch method {
        case .directLocate:
            print("[hash method]: directLocate")
            let a = 10
            let b = 8
            return a * ele + b
        case .getReminder:
            print("[hash method]: getReminder")
            return ele % eleCount
        }
    }
    
    func conflictFunc(ele: Int, method: ConflictMethod) -> Int {
        switch method {
        case .linearProbe:
            print("[conflict method]: linearProbe")
            return (ele + 1) % eleCount
        case .randomProbe:
            print("[conflict method]: randomProbe")
            let r = Int(arc4random_uniform(8))
            return (ele + r) % eleCount
        }
    }
    
    func showHT(){
        for (key, value) in hashTable {
            print("key: \(key), value: \(value)")
        }
    }
    
    func search(ele: Int) -> Int {
        let k = getValidKey(ele: ele)
        return hashTable[k]!
    }
    
    func getValidKey(ele: Int) -> Int {
        //let's manipulate k
        var k: Int
    
        k = hashFunc(ele: ele, method: self.usedHashM)
        if hashTable[k] == nil {
            return k
        } else {
            var tempE = ele
            while(hashTable[k] != nil) {
                k = conflictFunc(ele: tempE, method: self.usedConflictM)
                tempE += 1
            }
            return k
        }
    }
}
