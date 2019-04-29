package A02;

/*
 * Test for JavaFx
 */
import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;


public class HelloWorld extends Application {

    public void start(Stage primaryStage) throws Exception {
        try {
            primaryStage.setTitle("Hello World!");

            Group root = new Group();
            Scene scene = new Scene(root, 500, 500);
            primaryStage.setScene(scene);

            //
            Text t = new Text("Good Morning!");
            root.getChildren().add(t);
            t.setX(100);
            t.setY(100);
            t.setFont(Font.font("Tahoma", FontWeight.BLACK, 30));
            t.setFill(Color.BISQUE);

            Button b1 = new Button();

            Button b2 = new Button("Login");

            primaryStage.show();
        } catch (Error e) {
            Throwable cause = e.getCause();
            //System.out.println(cause.getMessage());
        }

    }

    public static void main(String[] args) {
        launch(args);
    }
}

