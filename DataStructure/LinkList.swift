class LinkList<T>: CustomDebugStringConvertible, ExpressibleByArrayLiteral {
    var head: Node?
    var tail: Node?
    typealias Element = T
    
    required init(arrayLiteral elements: Element...) {
        for i in elements {
            if head == nil {
                let newNode = Node(data: i)
                self.head = newNode
                self.tail = newNode
            } else {
                let newNode = Node(data: i)
                self.tail?.next = newNode
                self.tail = newNode
            }
        }
    }
    
    var debugDescription: String {
        var a: String = ""
        guard head != nil else { return "empty list" }
        a += head!.debugDescription
        
        var currentNode = head!
        while(true){
            guard let nextNode = currentNode.next else { break }
            a += nextNode.debugDescription
            currentNode = nextNode
        }
        
        return a
    }
    
    class Node: CustomDebugStringConvertible {
        var data: T
        var next: Node?
        
        init(data: T){
            self.data = data
        }
        
        var debugDescription: String {
            var a: String = ""
            if next != nil {
                a += "\(self.data) -> "
            } else {
                a += "*"
            }
            return a
        }
    }
}
