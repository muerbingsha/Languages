// vector assign
#include <iostream>
#include <vector>

//good point: no need to specify type
#define get_array_len(array, len) { len = (sizeof(array)/sizeof(array[0])); }


int main ()
{
    std::vector<int> first;
    std::vector<int> v_positions;
    std::vector<int> v_normals;
    
    
    //[8, 8, 8]
    v_positions.assign(3, 8);
    std::cout << "size of v_positions: " << int(v_positions.size()) << '\n';
    
    // assigning from array.
    int n[] = {0, 1, 0};
    int ns;
    get_array_len(n, ns);
    v_normals.assign(n, n + ns);
    std::cout<< "size of v_normals: " << (int)v_normals.size() << '\n';
    
    // assign from another vector
    std::vector<int>::iterator i;
    i = v_positions.begin() + 1;
    
    first.assign(i, v_positions.end() -1);
    std::cout << "Size of first: " << int (first.size()) << '\n';  // the 1 central values of v_positions
    
    return 0;
}
