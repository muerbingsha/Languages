package DataStructure;

public interface List<T> {

    boolean add(T element);
    T get(int index);
    T remove(int index);
    int size();
    boolean contains(T element);
    boolean reverse();
    String toString();
}
