import streamlit as st
import subprocess
import os

st.title("Extended MST (C Kruskal) with Node Weights")

st.write("Input format:")
st.code("""
num_nodes num_edges
node_weight[1] node_weight[2] ... node_weight[n]
u1 v1 edge_weight1
...
um vm edge_weightm
""", language="text")

# Default input example
default_input = """\
4 4
3 2 4 1
1 2 5
2 3 6
3 4 2
4 1 3
"""

inp = st.text_area("Input data", value=default_input, height=260)

def compile_and_run(input_data: str) -> str:
    if not os.path.exists("mst.c"):
        return "mst.c not found in the working directory."

    # Compile mst.c
    compile_cmd = ["gcc", "mst.c", "-o", "mst_exec"]
    compile_proc = subprocess.run(compile_cmd, capture_output=True, text=True)
    if compile_proc.returncode != 0:
        return f"Compilation failed:\n{compile_proc.stderr}"  # <-- fixed

    # Run the executable
    run_cmd = ["./mst_exec"]
    try:
        run_proc = subprocess.run(
            run_cmd,
            input=input_data.strip(),
            capture_output=True,
            text=True,
            timeout=20
        )
    except subprocess.TimeoutExpired:
        return "Execution timed out."

    if run_proc.returncode != 0:
        return f"Execution failed:\n{run_proc.stderr}"  # <-- fixed

    return run_proc.stdout.strip()
