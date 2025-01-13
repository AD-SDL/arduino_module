"""
REST-based node that interfaces with WEI and provides a USB camera interface
"""

from pathlib import Path
import subprocess
import serial.tools.list_ports
from fastapi.datastructures import State
from wei.modules.rest_module import RESTModule
from wei.types.module_types import LocalFileModuleActionResult
from wei.types.step_types import (
    ActionRequest,
    StepFileResponse,
    StepResponse,
    StepStatus,
)
from wei.utils import extract_version

rest_module = RESTModule(
    name="arduino_node",
    version=extract_version(Path(__file__).parent.parent / "pyproject.toml"),
    description="An example REST arduino  implementation",
    model="arduino",
)
rest_module.arg_parser.add_argument(
    "--arduino_address", type=str, help="the arduino address", default="/dev/ttyACM0"
)


@rest_module.action(
    name="flash", description="An action that flashes a sketch onto the arduino",
)

def flash(
    state: State,
    action: ActionRequest,
) -> StepResponse:
    """Function to flash arduino"""
    result = subprocess.run(['ls', '-lrth'], capture_output=True, text=True)
    print('Output:', result.stdout)
    sketch_name = "src.ino"
    sketch_path = Path("/home/app/arduino_module/src").expanduser() / sketch_name
    sketch_path.parent.mkdir(parents=True, exist_ok=True)
    try:
        subprocess.run(['bash', '-c', 'cd .. && pwd']) 
        subprocess.run(["/home/app/arduino_module/src/compileAndUpload.sh"], check=True)

    except Exception:
        print("Arduino unavailable, returning empty image")

    return StepResponse(status=StepStatus.SUCCEEDED)

if __name__ == "__main__":
    rest_module.start()
