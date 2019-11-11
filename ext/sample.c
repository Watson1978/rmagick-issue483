#include <ruby.h>
#include <unistd.h>

VALUE
sample_test(VALUE self)
{
    int status = 0;
    int child_status = 0;
    pid_t child_pid = fork();


    if (child_pid == 0) {
        char *const args[] = {
            "/bin/sleep",
            "1",
            NULL
        };
        status = execvp(args[0], args);
        exit(0);
    }
    else {
        pid_t pid;

        pid = waitpid(child_pid, &child_status, 0);
        if (pid == -1) {
            status = -1;
            perror("Error waitpid()");
        }
        else {
            if (WIFEXITED(child_status)) {
                // Expected path
                status = WEXITSTATUS(child_status);
                printf("(1) WIFEXITED : status = %d\n", status);
            }
            else if (WIFSIGNALED(child_status)) {
                status = -1;
                printf("(2) WIFSIGNALED : status = %d\n", status);
            }
        }
    }


    return INT2FIX(status);
}

void Init_sample(void)
{
    VALUE rb_cSample = rb_define_class("Sample", rb_cObject);
    rb_define_method(rb_cSample, "test", sample_test, 0);
}
