package stFunctionInterface;

/*
 * @FunctionInterface is a useful tool to check whether the interface only has one abstract method
 */
@FunctionalInterface
public interface GreetingService {
    void sayMessage(String name);

    default void say() {

    }
}
