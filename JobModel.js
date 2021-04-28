function init()
{
    var priority = false;
    var curr_alg = algorithm_comboBox.valueAt(algorithm_comboBox.currentIndex);

    algorithm_comboBox.displayText = curr_alg;
    preemtive_checkBox.visible = false;
    priority_rectangle.visible = false;
    time_quantum_rectangle.visible = false;

    if( curr_alg === "FCFS")
    {
        jobModel.initTable(priority)
    }
    else if(curr_alg === "Priority")
    {
        priority = true;
        preemtive_checkBox.visible = true;
        priority_rectangle.visible = true;
        jobModel.initTable(priority)
    }
    else if(curr_alg === "SJF")
    {
        priority = true;
        preemtive_checkBox.visible = true;
        priority_rectangle.visible = true;
        jobModel.initTable(priority)


    }
    else
    { // Round Robin
        time_quantum_rectangle.visible = true;
        jobModel.initTable(priority);
    }
}

function cleanInputFields()
{
    process_name_textEdit.text = "";
    burst_time_textEdit.text = "";
    arrival_time_textEdit.text = "";
    priority_textEdit.text = "";
    process_name_rectangle.border.color = "black";
    arrival_time_rectangle.border.color = "black";
    burst_time_rectangle.border.color = "black";
    priority_rectangle.border.color = "black";
    time_quantum_rectangle.border.color = "black";
}

function validateInput()
{
    var status;
    var curr_alg = algorithm_comboBox.valueAt(algorithm_comboBox.currentIndex);

    if( curr_alg === "FCFS")
    {
        status = !(process_name_textEdit.text.length === 0) &&
                !(arrival_time_textEdit.text.length === 0) &&
                !(burst_time_textEdit.text.length === 0);
    }
    else if(curr_alg === "Priority" || curr_alg === "SJF")
    {
        status = !(process_name_textEdit.text.length === 0) &&
                !(arrival_time_textEdit.text.length === 0) &&
                !(burst_time_textEdit.text.length === 0)&&
                !(priority_textEdit.text.length === 0);
    }
    else
    {
        status = !(process_name_textEdit.text.length === 0) &&
                !(arrival_time_textEdit.text.length === 0) &&
                !(burst_time_textEdit.text.length === 0)&&
                !(time_quantum_textEdit.text.length === 0);
    }

    return status;
}

function addProcess()
{

    console.log(typeof(process_name_textEdit.text));
    if(validateInput())
    {
        var list_str = [];
        list_str.push(process_name_textEdit.text);
        list_str.push(burst_time_textEdit.text);
        list_str.push(arrival_time_textEdit.text);
        list_str.push(priority_textEdit.text);
        list_str.push(time_quantum_textEdit.text);
        list_str.push((preemtive_checkBox.checked)? 1:0);
        list_str.push( algorithm_comboBox.valueAt(algorithm_comboBox.currentIndex));
        jobModel.addProcess(list_str);
        cleanInputFields();
    }
    else
    {
        process_name_rectangle.border.color = (process_name_textEdit.text.length === 0)? "red":"black";
        arrival_time_rectangle.border.color = (arrival_time_textEdit.text.length === 0)? "red":"black";
        burst_time_rectangle.border.color = (burst_time_textEdit.text.length === 0)? "red":"black";
        priority_rectangle.border.color = (priority_textEdit.text.length === 0)? "red":"black";
        time_quantum_rectangle.border.color = (time_quantum_textEdit.text.length === 0)? "red":"black";
    }
}

function removeProcess()
{
    jobModel.removeProcess();
}

function clearTable()
{
    jobModel.clearTable();
    cleanInputFields();
}
