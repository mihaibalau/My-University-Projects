package GUI;

import Exceptions.MyException;
import Model.availablePrograms;
import Model.statements.IStmt;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import Controller.Controller;

public class SelectorFXController {

    private Controller controller;
    private AppFXController mainWindowController;


    @FXML
    private Button selectButton;
    @FXML
    private ListView<IStmt> programsList;
    @FXML
    private Label errorMessage;

    public SelectorFXController(Controller _controller, AppFXController _mainWindowController){
        this.controller = _controller;
        this.mainWindowController = _mainWindowController;
    }

    @FXML
    public void initialize() {
        programsList.setItems(FXCollections.observableList(availablePrograms.availablePrograms));
        selectButton.setOnAction(actionEvent -> {
                try {
                    int index = programsList.getSelectionModel().getSelectedIndex();
                    if (index < 0) {
                        throw new MyException("No index selected!");
                    } else if (index >= availablePrograms.availablePrograms.size()) {
                        throw new MyException("No program at selected index!");
                    }
                    this.errorMessage.setText("");
                    this.controller.setProgram(availablePrograms.availablePrograms.get(index));
                } catch (MyException e) {
                    this.errorMessage.setText("ERROR: " + e.getMessage());
                } finally {
                    mainWindowController.refresh();
                }
            }
        );
    }
}
