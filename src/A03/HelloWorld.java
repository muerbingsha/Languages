package A03;

/*
 * Stanford Scene Graph - Test1
 */
import edu.stanford.nlp.scenegraph.RuleBasedParser;
import edu.stanford.nlp.scenegraph.SceneGraph;


public class HelloWorld {
    public static void main(String[] args) {
        String sentence = "A brown fox chases a white rabbit.";
        RuleBasedParser parser = new RuleBasedParser();

        SceneGraph sg = parser.parse(sentence);
        System.out.println(sg.toReadableString());

       // System.out.println(sg.toJSON());

        System.out.println(sg.toString());

    }
}
