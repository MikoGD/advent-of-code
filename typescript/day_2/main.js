const fs_2 = require('fs');
const input_puller_2 = (file_name) => {
    const input = fs_2.readFileSync(file_name, 'utf-8');
    const code_string = input.split(',');
    let code = code_string.map((val) => parseInt(val, 10));
    return code;
};
const run_opcode = (code, instruction_pointer) => {
    let temp_code = code;
    const opcode = temp_code[instruction_pointer];
    const param_1 = temp_code[instruction_pointer + 1];
    const param_2 = temp_code[instruction_pointer + 2];
    const param_3 = temp_code[instruction_pointer + 3];
    if (opcode == 1) {
        temp_code[param_3] = temp_code[param_1] + temp_code[param_2];
    }
    else if (opcode == 2) {
        temp_code[param_3] = temp_code[param_1] * temp_code[param_2];
    }
    return temp_code;
};
const run_program = (code) => {
    let temp_code = code;
    for (let i = 0; i < temp_code.length; i += 4) {
        if (temp_code[i] == 99) {
            break;
            return temp_code;
        }
        temp_code = run_opcode(temp_code, i);
    }
    return temp_code;
};
const get_solution_2 = () => {
    const code = input_puller_2('./day_2/input.txt');
    let temp_code;
    for (let noun = 0; noun < 100; noun++) {
        for (let verb = 0; verb < 100; verb++) {
            temp_code = Array.from(code);
            temp_code[1] = noun;
            temp_code[2] = verb;
            temp_code = run_program(temp_code);
            if (temp_code[0] == 19690720) {
                console.log(`noun = ${temp_code[1]}, verb = ${temp_code[2]}`);
                console.group(`(100 * noun) + verb = ${100 * temp_code[1] + temp_code[2]}`);
                return;
            }
        }
    }
    for (let verb = 0; verb < 100; verb++) {
        for (let noun = 0; noun < 100; noun++) {
            temp_code = Array.from(code);
            temp_code[1] = noun;
            temp_code[2] = verb;
            temp_code = run_program(temp_code);
            if (temp_code[0] == 19690720) {
                console.log(`noun = ${temp_code[1]}, verb = ${temp_code[2]}`);
                return;
            }
        }
    }
    console.log('Fail');
};
get_solution_2();
