package stJava.errors;
 
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
 
public class ReflectionExample {
 
    @SuppressWarnings("unused")
    private int testMethod(String str) {
        if(str.length() == 0)
            throw new IllegalArgumentException("The string must contain at least one character!");
 
        System.out.println("Inside testMethod: argument's value equals to: \"" + str + "\"");
 
        return 0;
    }
 
    public static void main(String... args) {
        try {
            // Retrieve an instance of the current class as an Object.
            Class<?> c = Class.forName("stJava.errors.ReflectionExample");
            Object t = c.newInstance();
 
            Method[] declaredMethods = c.getDeclaredMethods();
            for (Method method : declaredMethods) {
                String methodName = method.getName();
 
                // Skip the current main method.
                if(methodName.contains("main"))
                    continue;
 
                System.out.format("Invoking %s()%n", methodName);
                try {
                    // Declare the method as accessible.
                    method.setAccessible(true);
 
                    /* Invoke the method with a 'null' parameter value, in order
                     * for an exception to be thrown. */
                    Object returnValue = method.invoke(t, "");
 
                    System.out.format("%s() returned: %d%n", methodName, returnValue);
                }
                catch (InvocationTargetException ex) {
                    System.err.println("An InvocationTargetException was caught!");
                    Throwable cause = ex.getCause();
                    System.out.format("Invocation of %s failed because of: %s%n",
                            methodName, cause.getMessage());
                }
            }
        }
        catch (ClassNotFoundException | InstantiationException | IllegalAccessException ex) {
            System.err.println("The following exception was thrown:");
            ex.printStackTrace();
        }
    }
}