function init()
{
    var priority = false;
    var curr_alg = algorithm_comboBox.valueAt(algorithm_comboBox.currentIndex);
    preemtive_checkBox.visible = false;
    priority_rectangle.visible = false;
    time_quantum_rectangle.visible = false;

    algorithm_comboBox.displayText = curr_alg;
    if( curr_alg === "FCFS")
        tableModel.initTable(priority)
    else if(curr_alg === "Priority")
    {
        priority = true;
        preemtive_checkBox.visible = true;
        priority_rectangle.visible = (preemtive_checkBox.checked)? true: false;
        tableModel.initTable(priority)
    }
    else if(curr_alg === "SJF")
    {
        priority = true;
        preemtive_checkBox.visible = true;
        priority_rectangle.visible = (preemtive_checkBox.checked)? true: false;
        tableModel.initTable(priority)


    }
    else
    {
        // Round Robin
        time_quantum_rectangle.visible = true;
        tableModel.initTable(priority);
    }
}

function cleanInputFields()
{
    process_name_textEdit.text = "";
    burst_time_textEdit.text = "";
    arrival_time_textEdit.text = "";
    priority_textEdit.text = "";

}

function addProcess()
{
    //  check and validate input data
    var list_str = [];
    list_str.push(process_name_textEdit.text);
    list_str.push(burst_time_textEdit.text);
    list_str.push(arrival_time_textEdit.text);
    list_str.push(priority_textEdit.text);
    list_str.push(time_quantum_textEdit.text);
    list_str.push((preemtive_checkBox.checked)? 1:0);
    list_str.push( algorithm_comboBox.valueAt(algorithm_comboBox.currentIndex));
    tableModel.addProcess(list_str);
    cleanInputFields();
}


function removeProcess()
{
    tableModel.removeProcess();
}

function clearTable()
{

}
