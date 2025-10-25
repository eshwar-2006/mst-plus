import streamlit as st
from subprocess import run, PIPE

st.title("Extended MST: Nodes + Edges Weights")

# Input for nodes and edges
num_nodes = st.number_input("Number of nodes", min_value=1, value=4)
num_edges = st.number_input("Number of edges", min_value=1, value=5)

st.write("Enter edge data in format: u v edge_weight node_weight_u node_weight_v")

edge_data = st.text_area("Edges", "1 2 10 3 4\n2 3 5 4 2")

if st.button("Compute MST"):
    # Prepare input for C program
    input_str = f"{num_nodes} {num_edges}\n{edge_data}"
    
    # Run C executable
    result = run(['./mst_exec'], input=input_str.encode(), stdout=PIPE)
    st.success(result.stdout.decode())
import subprocess

input_str = """4 4
3 2 4 1
1 2 5
2 3 6
3 4 2
4 1 3
"""

result = subprocess.run(
    ["./mst_exec"],
    input=input_str.strip(),  # remove extra spaces
    capture_output=True,
    text=True,
    timeout=10
)

print(result.stdout)  # This should show the MST weight

