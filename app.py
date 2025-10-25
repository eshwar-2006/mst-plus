import streamlit as st
import subprocess
import os

st.title("Extended MST: Node + Edge Weights (C Kruskal)")

st.write("Input format:")
st.code("""
num_nodes num_edges
node_weight[1] node_weight[2] ... node_weight[n]
u1 v1 edge_weight1
...
um vm edge_weightm
""", language="text")

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
    if not os.path.exists("mst_ext.c"):
        return "mst_ext.c not found in the working directory."

    # Compile
    compile_cmd = ["gcc", "mst_ext.c", "-o", "mst_ext_exec"]
    proc = subprocess.run(compile_cmd, capture_output=True, text=True)
    if proc.returncode != 0:
        return f"Compilation failed:\n{proc.stderr}"

    # Run with input
    run_cmd = ["./mst_ext_exec"]
    try:
        proc = subprocess.run(run_cmd, input=input_data, capture_output=True, text=True, timeout=20)
    except subprocess.TimeoutExpired:
        return "Execution timed out."
    if proc.returncode != 0:
        return f"Execution failed:\n{proc.stderr}"
    return proc.stdout.strip()

if st.button("Compute MST"):
    with st.spinner("Computing..."):
        output = compile_and_run(inp)
    st.success("Result:")
    st.write(output)

st.caption("Note: The app compiles mst_ext.c on each run and feeds the input as a single string.")
