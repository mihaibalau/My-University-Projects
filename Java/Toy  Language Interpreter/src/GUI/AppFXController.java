package GUI;

import Controller.Controller;
import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myHeap.MyIHeap;
import Model.dataStructures.myList.MyIList;
import Model.prgState.PrgState;
import Model.statements.IStmt;
import Model.values.StringValue;
import Model.values.Value;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Pair;

import java.io.BufferedReader;
import java.util.List;

public class AppFXController {

    private Controller controller;
    MyIHeap<Integer, Value> heap;
    MyIDict<StringValue, BufferedReader> fileTable;
    MyIList<Value> out;

    @FXML
    private Label prgStatesLabel;
    @FXML
    private ListView<String> exeStack;
    @FXML
    private ListView<Value> outList;
    @FXML
    private ListView<StringValue> fileList;
    @FXML
    private ListView<String> prgStates;
    @FXML
    private TableView<Pair<Integer, Value>> heapTable;
    @FXML
    private TableColumn<Pair<Integer, Value>, Integer> heapAddressColumn;
    @FXML
    private TableColumn<Pair<Integer, Value>, String> heapValueColumn;
    @FXML
    private TableView<Pair<String, Value>> symTable;
    @FXML
    private TableColumn<Pair<String, Value>, String> symNameColumn;
    @FXML
    private TableColumn<Pair<String, Value>, String> symValueColumn;
    @FXML
    private Button oneStepButton;
    @FXML
    private Button runButton;


    public AppFXController(Controller _controller){
        this.controller = _controller;
    }

    public void refresh(){
        int index = this.prgStates.getSelectionModel().getSelectedIndex();

        this.exeStack.getItems().clear();
        this.outList.getItems().clear();
        this.fileList.getItems().clear();
        this.prgStates.getItems().clear();
        this.heapTable.getItems().clear();
        this.symTable.getItems().clear();

        this.prgStatesLabel.setText("Current Program States: " + this.controller.getPrgStates().size());
        for(int i = 0; i < this.controller.getPrgStates().size(); i++){
            this.prgStates.getItems().add("Program State: " + i);
        }

        if(!this.controller.getPrgStates().isEmpty()){
            this.heap = this.controller.getPrgStates().get(0).getHeap();
            this.out = this.controller.getPrgStates().get(0).getOut();
            this.fileTable = this.controller.getPrgStates().get(0).getFileTable();
        }

        if(this.heap != null)
            this.heap.getHeap().forEach((x, y) -> this.heapTable.getItems().add(new Pair<>(x, y)));

        if(this.out != null)
            this.out.getList().forEach(x -> this.outList.getItems().add(x));

        if(this.fileTable != null)
            this.fileTable.getKeys().forEach(x -> this.fileList.getItems().add(x));

        if(index >= 0) {
            PrgState currentPrg;
            currentPrg = this.controller.getPrgStates().get(index);

            MyIDict<String, Value> symTbl;
            symTbl = currentPrg.getSymTable();
            symTbl.getDict().forEach((x, y) -> this.symTable.getItems().add(new Pair<>(x, y)));

            List<IStmt> stmtList = currentPrg.getExeStack().getReverse();
            for(int i = stmtList.size()-1; i >= 0; i--)
                this.exeStack.getItems().add(stmtList.get(i).toString());

            this.prgStates.getSelectionModel().select(index);
        }

        this.exeStack.refresh();
        this.prgStates.refresh();
        this.symTable.refresh();
        this.outList.refresh();;
        this.fileList.refresh();
        this.heapTable.refresh();

    }

    @FXML
    public void initialize(){
        this.heapAddressColumn.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getKey()).asObject());
        this.heapValueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue().toString()));
        this.symNameColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue().toString()));
        this.symValueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue().toString()));
        this.refresh();

        this.oneStepButton.setOnAction( actionEvent -> {
                try {
                    if (this.controller.getPrgStates().isEmpty())
                        throw new MyException("No program to be executed!");
                    this.prgStates.getSelectionModel().clearSelection();
                    this.controller.oneStep();
                } catch (Exception e) {
                    Alert alert = new Alert(Alert.AlertType.ERROR, e.toString(), ButtonType.CLOSE);
                    alert.showAndWait();
                } finally {
                    this.refresh();
                }
            }
        );

        this.runButton.setOnAction( actionEvent -> {
            try {
                prgStates.getSelectionModel().clearSelection();
                this.controller.fullExecution();
            } catch (Exception e){
                Alert alert = new Alert(Alert.AlertType.ERROR, e.toString(), ButtonType.CLOSE);
                alert.showAndWait();
            } finally {
                this.refresh();
            }
        });

        this.prgStates.setOnMouseClicked(x -> this.refresh());
    }

}
