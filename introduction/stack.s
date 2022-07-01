# ================================================== #
.text                                                #
.section .rodata                                     #
    .globl main                                      #
    .type main, @function                            #
                                                     #
    .data                                          # D #
    .len_stack:                                    # A #
        .long 0                                    # T #
    .printlen:                                     # A #
        .string "len: %d\n"                          #
        .text                                        #
    .printele:                                       #
        .string "element: %d\n"                      #
        .text                                        #
    .endstack:                                       #
        .string "--end stack--\n"                    #
        .text                                        #
    .empty_stack:                                    #
        .string "--empty stack--\n"                  #
        .text                                        #
# ================================================== #

print_len_stack:
    movl .len_stack(%rip), %esi
    leaq .printlen(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    ret

push_value:
    # `addq $4, %rbp` is beacause all values in the
    # stack are of 32 bit (4 bytes), %rbp register
    # will be somewhere, but there will be the value
    # set on %r14d register.
    addq $4, %rbp
    movl %r14d, (%rbp)
    movl .len_stack(%rip), %eax
    incl %eax
    movl %eax, .len_stack(%rip)
    ret

is_empty:
    # When the stack is empty this function will
    # be called just to print the information
    # message.
    leaq .empty_stack(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    ret

pop_value:
    # If there are elements in the stack
    # the pop operation could be done,
    # call to is_empty function otherwise
    # to don't get errors.
    cmpl $0, .len_stack(%rip)
    je is_empty
    # In the current position where %rbp points
    # will be set 0 as value, then %rbp will be
    # decreased by 4 (The necessary space to the
    # value that was removed).
    movl $0, (%rbp)
    subq $4, %rbp
    movl .len_stack(%rip), %eax
    decl %eax
    movl %eax, .len_stack(%rip)
    ret

print_element:
    # Prints the current element where %rbp register
    # points.
    movl (%rbp), %esi
    leaq .printele(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    # Something like: index--
    decl %r15d
    # To get the next element in the stack
    # %rbp gotta be decreased by 4.
    subq $4, %rbp
    call print_loop
    ret
print_loop:
    # %r15d works as index, while %r15d is not
    # zero still there are elements.
    cmpl $0, %r15d
    jg print_element
    ret
print_stack:
    # Getting the value of %rbp and setting it
    # in %r14 since %rbp will be modified.
    movq %rbp, %r14
    # Getting the size of the stack.
    movl .len_stack(%rip), %r15d
    call print_loop
    # Setting the initial value of %rbp
    # to don't lost the values.
    movq %r14, %rbp
    leaq .endstack(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    ret

# ------------------------------------------------------------------------ SORT
sort_swap:
    # So, at this point %eax saves the next value, now
    # r14d will save the current value.
    movl (%rbp), %r14d
    # Swapping.
    movl %r14d, -4(%rbp)
    movl %eax, (%rbp)
    ret
sort_body:
    # eax will save the next value in the stack
    # (%rbp) is the current value in the stack
    movl -4(%rbp), %eax
    # The stack will be sorted by maximum to minimum
    # so if the next value is greater than the current
    # must be swapped (eax < (%rbp)).
    cmpl %eax, (%rbp)
    jl sort_swap
    # decreasing the indexes
    decl %r15d
    subq $4, %rbp
    call sort_loop
    ret
sort_loop:
    # %r15d works as index again, same
    # process than in print function.
    cmpl $1, %r15d
    jge sort_body
    ret
sort_pre:
    # index of the first loop must be decreased
    decl %ebx
    movq %rbp, %rdx
    movl .len_stack(%rip), %r15d
    call sort_loop
    movq %rdx, %rbp
    call sort_call
    ret
sort_call:
    # To sort the stack there must be two loops
    # and this is one of them, from len_stack to
    # 0 included.
    cmp $0, %ebx
    jge sort_pre
    ret
sort_init:
    movl .len_stack(%rip), %ebx
    call sort_call
    ret
# ------------------------------------------------------------------------ SORT

main:
    # This is a complex concept.
    pushq %rbp
    movq %rsp, %rbp

    # ----------------- CURRENT STACK ----------- #
    movl $7, %r14d    # %rbp's values  | values |
    call push_value   #      -16(%rbp) |   7    |
    movl $1, %r14d    #      -12(%rbp) |   1    |
    call push_value   #       -8(%rbp) |   3    |
    movl $3, %r14d    #       -4(%rbp) |  -2    |
    call push_value   #       (%rbp)   |   5    |
    movl $-2, %r14d   # That's the assembly
    call push_value   # representation, our stack
    movl $5, %r14d    # looks like:
    call push_value   # [5, -2, 3, 1, 7].
    # ------------------------------------------- #
    call print_stack
    call sort_init

    call print_stack
    call print_len_stack

    call pop_value
    call print_stack
    call print_len_stack

    # return 0;
    movq $60, %rax
    movq $0, %rdi
    syscall
    leave
    ret
