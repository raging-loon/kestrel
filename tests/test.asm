section .data:
    kdl_rule_test_data_str_test db "LowLevelKeyBoardProc\0"

caller:
    mov edx, [kdl_rule_test_data_str_test]
    mov ebx, file_data
    call kdl_rule_test


kdl_rule_test:
    pusha 
    
    

    popa
    ret