package A02;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.util.Stack;

public class Test1 extends Application {
    @Override
    public void start(Stage stage) throws Exception {
        stage.setTitle("Test1");

        Button btn = new Button();
        btn.setText("Test 1 Button");
        btn.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                //System.out.println("Test 1 Button");
            }
        });

        StackPane sp = new StackPane();
        sp.getChildren().add(btn);
        stage.setScene(new Scene(sp, 300, 300));

        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
