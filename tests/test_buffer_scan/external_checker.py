"""Complies with vanilla testlib."""

from .base import *
from pathlib import Path
from os import access, X_OK
from subprocess import run, PIPE, CompletedProcess
from lib.utils.system import terminate_proc


class ExternalChecker(Checker):
    """
    Checker using an external binary file.
    """

    def __str__():
        return "external"

    def __init__(self, checker_path: Path, timeout=5) -> None:
        """
        Initialize the checker. `checker_path` is the path to the external binary checker.

        Will check for the path's executability; will terminate the entire Python interpreter
        if this check fails.
        """
        self.path = checker_path
        self.timeout = timeout

        if not access(self.path, X_OK):
            terminate_proc(
                f"Internal critical error: external checker {self.path} isn't executable."
            )

    def check(self, input: bytes, answer: bytes, output: bytes) -> CheckerResult:
        """Check result using external checker in `checker_path`.

        Sequentially pass `input`, `output` and `answer` to checker's `stdin`.

        The C++ checker, when executed, will be supplemented with the following arguments (in `argv[]`):
        - `--_asimon_sz_input X`
        - `--_asimon_sz_answer Y`
        - `--_asimon_sz_output Z`

        meaning that the first `X` bytes of `stdin` is `input`, the next `Y` bytes is `answer`, and the last `Z` bytes is `output`.

        Using these arguments, the checker or one of its included libraries must implement a function that decodes
        `stdin` back to the three aforementioned streams. An example can be seen in the ASIMON-testlib compatibility
        layer at /src/workspace/lib/testlib.h.

        Any message from the C++ checker must be passed to `stderr`; this method will not check `stdout`'s content.
        """
        from uuid import uuid4
        from lib.config.paths import bindir

        input_file = uuid4()
        answer_file = uuid4()
        output_file = uuid4()

        input_file = Path(bindir / f"{input_file}.txt")
        output_file = Path(bindir / f"{output_file}.txt")
        answer_file = Path(bindir / f"{answer_file}.txt")

        with open(input_file, "wb") as ifs, open(output_file, "wb") as ofs, open(
            answer_file, "wb"
        ) as ass:
            ifs.write(input)
            ofs.write(output)
            ass.write(answer)

        # input_buffer = b"".join([input, answer, output])

        # proc: CompletedProcess = run(
        #     [
        #         self.path,
        #         "--_asimon_sz_input",
        #         str(len(input)),
        #         "--_asimon_sz_answer",
        #         str(len(answer)),
        #         "--_asimon_sz_output",
        #         str(len(output)),
        #     ],
        #     input=input_buffer,
        #     stdout=PIPE,
        #     stderr=PIPE,
        # )

        import time

        a = time.time()
        proc: CompletedProcess = run(
            [self.path, input_file, output_file, answer_file],
            stdout=PIPE,
            stderr=PIPE,
        )

        import os

        os.remove(input_file)
        os.remove(output_file)
        os.remove(answer_file)

        print(time.time() - a)
        status = ContestantExecutionStatus(proc.returncode)
        if status == ContestantExecutionStatus.FAIL:
            terminate_proc(proc.stderr.decode())

        return CheckerResult(
            status,
            proc.stderr.decode(),  # testlib outputs its comment here
        )
