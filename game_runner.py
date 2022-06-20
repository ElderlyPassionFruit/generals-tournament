import socket
import subprocess
import sys
from time import sleep

if __name__ == "__main__":
    configpath = sys.argv[1]
    print("config path =", configpath)
    with open(configpath, "r") as f:
        programs = [line.strip() for line in f.readlines()[2:]]
    n = int(programs[0])
    programs_files = programs[1:]
    print("number of players =", n)
    print("programs_files =", programs_files)

    PROGRAM_CMDS = {}

    for i in range(len(programs_files)):
        PROGRAM_CMDS[i + 1] = "./" + programs_files[i]

    INTERACTOR_CMD = "./bin/generals-tournament"

    programs = {i : subprocess.Popen(cmd, stdin = subprocess.PIPE, stdout = subprocess.PIPE) for (i, cmd) in PROGRAM_CMDS.items()}
    cur_program = 0

    with subprocess.Popen(args = [INTERACTOR_CMD, configpath], stdin = subprocess.PIPE, stdout = subprocess.PIPE) as interactor:
        try:
            n = 0
            m = 0
            k = 0
            alive = [True] * (len(programs) + 1)
            first_line = True
            while interactor.poll() is None:
                cur_program += 1
                if len(programs) < cur_program:
                    cur_program = 1
                    first_line = False
                if not (programs[cur_program].poll() is None) or not alive[cur_program]:
                    # print(alive, cur_program)
                    continue
                # print("cur_program =", cur_program)
                # print(alive)
                line = ""
                if first_line:
                    line = interactor.stdout.readline()
                    # print("line1 =", line)
                    programs[cur_program].stdin.write(line)
                    n, m, k, _ = line.split()
                    n = int(n)
                    m = int(m)
                    k = int(k)

                ok = True
                # print(k + n * m + 1)
                must_finished = False
                for i in range(k + n * m + 1):
                    line = interactor.stdout.readline()
                    # print("line2", line)
                    if i == 0 and not line in [b"0\n", b"1\n"]:
                        must_finished = True
                        break
                    # print("line2 =", line)
                    programs[cur_program].stdin.write(line)
                    if i == 0 and line == b'0\n':
                        alive[cur_program] = False
                        ok = False
                        break
                if must_finished:
                    break
                programs[cur_program].stdin.flush()

                if ok:
                    move = programs[cur_program].stdout.readline()
                    # print("move =", move)
                    interactor.stdin.write(move)
                    interactor.stdin.flush()
                # sleep(0.05)
        except StopIteration:
            pass

    interactor.kill()

    print("Interactor exited, terminating children")
    for (i, prog) in programs.items():
        print(f"Terminating id {i}")
        prog.kill()
