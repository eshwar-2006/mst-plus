import streamlit as st
import subprocess
from subprocess import PIPE

st.title("Extended MST: Node + Edge Weights")

input_data = st.text_area(
    "Enter input in format:\nnum_nodes num_edges\nnode_weights (space separated)\nedges (u v weight)",
    "4 5\n3 4 1 2\n1 2 10\n2 3 5\n3 4 8\n1 3 7\n2 4 6"
)

if st.button("Compute MST"):
    # Compile C program at runtime
    compile_result = subprocess.run(['gcc', 'mst.c', '-o', 'mst_exec'])
    if compile_result.returncode != 0:
        st.error("Compilation failed")
    else:
        # Run the C executable
        result = subprocess.run(['./mst_exec'], input=input_data.encode(), stdout=PIPE)
        st.success("MST Weight: " + result.stdout.decode())

