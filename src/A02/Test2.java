package A02;

import com.sun.javafx.css.StyleCacheEntry;
import javafx.animation.*;
import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.util.Duration;


public class Test2 extends Application {
    @Override
    public void start(Stage stage) throws Exception {
        stage.setTitle("Test 2");

        // set scene
        Group root = new Group();
        Scene scene = new Scene(root, 300, 300);
        stage.setScene(scene);

        // add rectangle
        Rectangle rec = new Rectangle(0, 0, 50, 50);
        root.getChildren().add(rec);

        // set animation key value
        KeyValue kv1 = new KeyValue(rec.opacityProperty(), 0);
        KeyValue kv2 = new KeyValue(rec.xProperty(), 100, Interpolator.EASE_OUT);
        KeyFrame kf = new KeyFrame(Duration.millis(1000), kv1, kv2);

        Timeline time = new Timeline();
        time.setAutoReverse(true);
        time.setCycleCount(Animation.INDEFINITE);

        time.getKeyFrames().add(kf);

        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
